#include "z80.h"
#include "struct.h"
#include "define.h"

unsigned int	get_color(int color_bit, unsigned char palette, t_mem *mem)
{
	unsigned int color = (((palette >> (color_bit + 1)) & 1) << 1) + ((palette >> color_bit) & 1);
	if (color == 0)
		color = WHITE;
	else if (color == 1)
		color = LIGHT_GREY;
	else if (color == 2)
		color = DARK_GREY;
	else
		color = BLACK;
	return (color);
}

void	render_sprites(t_mem *mem)
{
	unsigned char lcdControl = R_LCDC;
	int usebig = 0;
	if (CHECK_BIT(2, lcdControl))
		usebig = 1;
	for (int sprite = 0; sprite < 40; sprite++)
	{
		unsigned char index = sprite * 4;
		unsigned char positionY = read(0xfe00 + index, mem) - 16;
		unsigned char positionX = read(0xfe00 + index + 1, mem) - 8;
		unsigned char tileLoc = read(0xfe00 + index + 2, mem);
		unsigned char attributes = read(0xfe00 + index + 3, mem);
		int yFlip = CHECK_BIT(6, attributes);
		int xFlip = CHECK_BIT(5, attributes);

		int scanline = R_LY;
		int height = 8;
		if (usebig)
			height = 16;
		if ((scanline >= positionY) && (scanline < (positionY + height)))
		{
			int line = scanline - positionY;
			if (yFlip)
			{
				line -= height;
				line *= -1;
			}
			line *= 2;
			unsigned short address = (0x8000 + (tileLoc * 16) + line);
			unsigned char data1 = read(address, mem);
			unsigned char data2 = read(address + 1, mem);
			for (int tilePixel = 7; tilePixel >= 0; tilePixel--)
			{
				int colorbit = tilePixel;
				if (xFlip)
				{
					colorbit -= 7;
					colorbit *= -1;
				}
				int colorNum = CHECK_BIT(colorbit, data2);
				colorNum <<= 1;
				colorNum |= CHECK_BIT(colorbit, data1);
				unsigned char  val = CHECK_BIT(4, attributes) ? R_OBP1 : R_OBP0;
				unsigned char color = get_color(colorNum, val, mem);
				if (color == 0)
					continue ;
				int xPix = 0 - tilePixel;
				xPix += 7;
				int pixel = positionX + xPix;
				if (scanline < 0 || scanline > 143 || pixel < 0 || pixel > 159)
					continue ;
				mem->sdl->pixel_lcd[pixel + (scanline * 160)] = color;
			}
		}
	}
}

unsigned short	get_memory_areas(t_mem *mem, unsigned short *tile_data, int *sign, int *win)
{
	if (CHECK_BIT(4, R_LCDC))
		*tile_data = 0x8000;
	else
	{
		*tile_data = 0x8800;
		*sign = 1;
	}
	if (CHECK_BIT(5, R_LCDC) && R_WY <= R_LY)
	{
		*win = 1;
		if (CHECK_BIT(6, R_LCDC))
			return (0x9c00);
		else
			return (0x9800);
	}
	else
	{
		if (CHECK_BIT(3, R_LCDC))
			return (0x9c00);
		else
			return (0x9800);
	}
	return (0);
}

void	render_tiles(t_mem *mem)
{
	int i = 0;
	unsigned short tile_location, tile_data, memory, tile_id_addr, tile_id;
	int sign = 0, win = 0;
	int y = R_LY, color_bit, color_id;

	unsigned short tile_row, tile_col;
	unsigned char b1, b2;
	unsigned char xpos, ypos, scrollx = R_SCX, windowx = R_WX - 7;
	memory = get_memory_areas(mem, &tile_data, &sign, &win);
	if (win)
		ypos = R_LY - R_WY;
	else
		ypos = R_LY + R_SCY;
	tile_row = ((unsigned char)(ypos / 8)) * 32;
	ypos %= 8;
	for (i = 0; i < 160; i++)
	{
		if (win && i >= windowx)
			xpos = i - windowx;
		else
			xpos = i + scrollx;
		tile_col = xpos / 8;
		tile_id_addr = memory + tile_row + tile_col;
		tile_id = read(tile_id_addr, mem);
		if (sign)
			tile_location = ((char)(tile_id) + 128) * 16 + tile_data;
		else
			tile_location = tile_id * 16 + tile_data;
		b1 = read(tile_location + ypos * 2, mem);
		b2 = read(tile_location + ypos * 2 + 1, mem);
		color_bit = ((xpos % 8) - 7) * -1;
		color_id = (CHECK_BIT(color_bit, b2) << 1) + CHECK_BIT(color_bit, b1);
		mem->sdl->pixel_lcd[i + (y * 160)] = get_color(color_id * 2, R_BGP, mem);
	}
}

void	draw_scanline(t_mem *mem)
{
	if (CHECK_BIT(0, R_LCDC))
		render_tiles(mem);
	if (CHECK_BIT(1, R_LCDC))
		render_sprites(mem);
}


void	lcdstart(t_mem *mem)
{
	mem->memory->wy = R_WY;
	mem->memory->wyc = 0;
}

int		update_graphics(t_mem *mem)
{
	int frame = 1;
	mem->timer->lcd_count += mem->last_cycle;
	
	if (mem->timer->lcd_count > 456)
	{
		mem->timer->lcd_count -= 456;
		if (R_LY == R_LYC)
		{
			R_STAT |= 4;
			if (R_STAT & 0x40)
				R_IF |= 2;
		}
		else
			R_STAT &= 0xfb;
		R_LY = (R_LY + 1) % 154;
		if (R_LY == 144)
		{
			mem->memory->lcd_mode = 1;
			frame = 0;
			R_IF |= 1;
			if (R_STAT & 0x10)
				R_IF |= 2;
		}
		else if (R_LY < 144)
		{
			if (R_LY == 0)
				lcdstart(mem);
			mem->memory->lcd_mode = 0;
			if (R_STAT & 8)
				R_IF |= 2;
		}
	}
	else if (mem->memory->lcd_mode == 0 && mem->timer->lcd_count >= 204)
	{
		mem->memory->lcd_mode = 2;
		if (R_STAT & 0x20)
			R_IF |= 2;
	}
	else if (mem->memory->lcd_mode == 2 && mem->timer->lcd_count >= 284)
	{
		mem->memory->lcd_mode = 3;
		draw_scanline(mem);
	}
	return (frame);
}
