#include "z80.h"
#include "struct.h"
#include "define.h"

unsigned int	get_color(int color_bit, t_mem *mem)
{
	unsigned char palette = read(*mem->io_reg->ff47, mem);
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
//	printf("here\n");
	for (int i = 0; i < 160; i++)
	{
		if (win && i >= windowx)
			xpos = i - windowx;
		else
			xpos = i + scrollx;
		tile_col = xpos / 8;
		tile_id_addr = memory + tile_row + tile_col;
		tile_id = read(tile_id_addr, mem);
		if (sign)
			tile_location = ((char)(tile_id) + 128) * 16;
		else
			tile_location = tile_id * 16;
		b1 = read(tile_location + ypos * 2, mem);
		b2 = read(tile_location + ypos * 2 + 1, mem);
		color_bit = ((xpos % 8) - 7) * -1;
		color_id = (CHECK_BIT(color_bit, b2) << 1) + CHECK_BIT(color_bit, b1);;
		
		mem->sdl->pixel_lcd[i + (y * 256)] = get_color(color_id * 2, mem);
	}
}

void	draw_scanline(t_mem *mem)
{
	if (CHECK_BIT(0, *mem->io_reg->ff40))
		render_tiles(mem);
/*	if (CHECK_BIT(1, *mem->io_reg->ff40))
		render_sprites(mem);
*/
}

void	set_lcd_status(t_mem *mem)
{
	unsigned char mode;
	unsigned char cur_mode;
	unsigned char reguest = 0;

	if (CHECK_BIT(7, *mem->io_reg->ff40) == 0)
	{
		mem->timer->scanline_counter = 456;
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
		if (mem->timer->scanline_counter > 376) //i think it should be just '>'
		{
			mode = 2;
			SET_BIT(1, *mem->io_reg->ff41);
			CLEAR_BIT(0, *mem->io_reg->ff41);
			reguest = CHECK_BIT(5, *mem->io_reg->ff41);
		}
		//mode3
		else if (mem->timer->scanline_counter > 204) //i think it should be just '>'
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

void	update_graphics(t_mem *mem)
{
	set_lcd_status(mem);
	if (CHECK_BIT(7, *mem->io_reg->ff40) == 1)
	{
		mem->timer->scanline_counter -= mem->last_cycle;
		if (mem->timer->scanline_counter <= 0)
		{
			*mem->io_reg->ff44 += 1;
			mem->timer->scanline_counter = 456;
			if (*mem->io_reg->ff44 == 144)
				SET_BIT(0, *mem->io_reg->ff0f);
			else if (*mem->io_reg->ff44 > 153)
				*mem->io_reg->ff44 = 0;
			else if (*mem->io_reg->ff44 < 143)
			{
				draw_scanline(mem);
			}
		}
	}
}
