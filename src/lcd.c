#include "z80.h"
#include "struct.h"
#include "define.h"

void	draw_scanline(t_mem *mem)
{
/*	if (CHECK_BIT(0, *mem->io_reg->ff40))
		render_tiles(mem);
	if (CHECK_BIT(1, *mem->io_reg->ff40))
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
