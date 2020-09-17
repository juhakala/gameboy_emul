#include "z80.h"
#include "struct.h"
#include "define.h"

void	update_graphics(t_mem *mem)
{
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
//				draw_scanline(mem);
			}
		}
	}
}
