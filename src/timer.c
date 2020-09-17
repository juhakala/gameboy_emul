#include "z80.h"
#include "struct.h"
#include "define.h"

void	set_timer_counter(t_mem *mem)
{
	if ((*mem->io_reg->ff04 & 3) == 0)
		mem->timer->timer_counter = 1024;
	else if ((*mem->io_reg->ff04 & 3) == 1)
		mem->timer->timer_counter = 16;
	else if ((*mem->io_reg->ff04 & 3) == 2)
		mem->timer->timer_counter = 64;
	else
		mem->timer->timer_counter = 256;
}


void	div_register(t_mem *mem)
{
	*mem->io_reg->ff04 += mem->last_cycle;
	if (*mem->io_reg->ff04 >= 255)
	{
		*mem->io_reg->ff04 = 0;
		*mem->io_reg->ff04 += 1;
	}
}

void	update_timer(t_mem *mem)
{
	div_register(mem);
	if ((*mem->io_reg->ff07 >> 2) & 1)
	{
		mem->timer->timer_counter -= mem->last_cycle;
		if (mem->timer->timer_counter <= 0)
		{
			set_timer_counter(mem);
			if (*mem->io_reg->ff05 == 255)
			{
				*mem->io_reg->ff05 = *mem->io_reg->ff06;
				SET_BIT(2, *mem->io_reg->ff0f);
			}
			else
				*mem->io_reg->ff05 += 1;
		}
	}
}
