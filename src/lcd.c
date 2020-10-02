
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
	unsigned char lcdControl = *mem->io_reg->ff40;
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

		int scanline = *mem->io_reg->ff44;
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
				unsigned char  val = CHECK_BIT(4, attributes) ? *mem->io_reg->ff49 : *mem->io_reg->ff48;
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
	if (CHECK_BIT(4, *mem->io_reg->ff40))
		*tile_data = 0x8000;
	else
	{
		*tile_data = 0x8800;
		*sign = 1;
	}
	if (CHECK_BIT(5, *mem->io_reg->ff40) && *mem->io_reg->ff4a <= *mem->io_reg->ff44)
	{
		*win = 1;
		if (CHECK_BIT(6, *mem->io_reg->ff40))
			return (0x9c00);
		else
			return (0x9800);
	}
	else
	{
		if (CHECK_BIT(3, *mem->io_reg->ff40))
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
	int y = *mem->io_reg->ff44, color_bit, color_id;

	unsigned short tile_row, tile_col;
	unsigned char b1, b2;
	unsigned char xpos, ypos, scrollx = *mem->io_reg->ff43, windowx = *mem->io_reg->ff4b - 7;
	memory = get_memory_areas(mem, &tile_data, &sign, &win);
	if (win)
		ypos = *mem->io_reg->ff44 - *mem->io_reg->ff4a;
	else
		ypos = *mem->io_reg->ff44 + *mem->io_reg->ff42;
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
		mem->sdl->pixel_lcd[i + (y * 160)] = get_color(color_id * 2, *mem->io_reg->ff47, mem);
	}
}

void	draw_scanline(t_mem *mem)
{
	if (CHECK_BIT(0, *mem->io_reg->ff40))
		render_tiles(mem);
	if (CHECK_BIT(1, *mem->io_reg->ff40))
		render_sprites(mem);
}

void	set_lcd_status(t_mem *mem)
{
	unsigned char mode;
	unsigned char cur_mode;
	unsigned char reguest = 0;

	if (CHECK_BIT(7, *mem->io_reg->ff40) == 0)
	{
		mem->timer->scanline_counter = 0;
		*mem->io_reg->ff44 = 0;
		*mem->io_reg->ff41 &= 252;
		SET_BIT(0, *mem->io_reg->ff41);
		return ;
	}
	cur_mode = *mem->io_reg->ff41 & 0x3;
	if (*mem->io_reg->ff44 >= 144)
	{
		mode = 1;
		SET_BIT(0, *mem->io_reg->ff41);
		CLEAR_BIT(1, *mem->io_reg->ff41);
		reguest = CHECK_BIT(4, *mem->io_reg->ff41);
	}
	else
	{
		//mode2
		if (mem->timer->scanline_counter <= 80) //i think it should be just '>'
		{
			mode = 2;
			SET_BIT(1, *mem->io_reg->ff41);
			CLEAR_BIT(0, *mem->io_reg->ff41);
			reguest = CHECK_BIT(5, *mem->io_reg->ff41);
		}
		//mode3
		else if (mem->timer->scanline_counter <= 252) //i think it should be just '>'
		{
			mode = 3;
			SET_BIT(0, *mem->io_reg->ff41);
			SET_BIT(1, *mem->io_reg->ff41);
		}
		//mode 0
		else
		{
			mode = 0;
			CLEAR_BIT(0, *mem->io_reg->ff41);
			CLEAR_BIT(1, *mem->io_reg->ff41);
			reguest = CHECK_BIT(3, *mem->io_reg->ff41);
		}
	}
	if (reguest && (mode != cur_mode))
		SET_BIT(1, *mem->io_reg->ff0f);
	if (*mem->io_reg->ff44 == *mem->io_reg->ff45)
	{
		SET_BIT(2, *mem->io_reg->ff41);
		if (CHECK_BIT(6, *mem->io_reg->ff41))
			SET_BIT(1, *mem->io_reg->ff0f);
	}
	else
		CLEAR_BIT(2, *mem->io_reg->ff41);
}
/*
void	update_graphics(t_mem *mem)
{
	set_lcd_status(mem);
	if (CHECK_BIT(7, *mem->io_reg->ff40) == 1)
	{
		mem->timer->scanline_counter += mem->last_cycle;
		if (mem->timer->scanline_counter >= 456)
		{
			*mem->io_reg->ff44 += 1;
			mem->timer->scanline_counter = 0;
			if (*mem->io_reg->ff44 == 144)
				SET_BIT(0, *mem->io_reg->ff0f);
			else if (*mem->io_reg->ff44 > 153)
				*mem->io_reg->ff44 = 0;
			else if (*mem->io_reg->ff44 < 144)
				draw_scanline(mem);
		}
	}
}
*/
void	update_graphics(t_mem *mem)
{
	mem->lcd_count += mem->last_cycle;
	if (mem->lcd_count > 456)
	{
		mem->lcd_count -= 456;
		if (R_LY == RLYC)
		{
			R_STAT |= 4;
			if (R_STAT & 0x40)
				R_IF |= 2;
		}
		else
			R_STAT &= 0xfb;
		RLY = (RLY + 1) % 154;
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
