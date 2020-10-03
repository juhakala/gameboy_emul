#include "z80.h"
#include "struct.h"
#include "define.h"

void	update_timer(t_mem *mem)
{
	int tac_cycles[4] = {1024, 16,64,256};
	
	mem->timer->div_count += mem->last_cycle;
	if (mem->timer->div_count > 256)
	{
		R_DIV++;
		mem->timer->div_count -= 256;
	}
	if (mem->timer->tac_enable)
	{
		mem->timer->tima_count -= tac_cycles[mem->timer->tac_rate];
		R_TIMA++;
		if (R_TIMA == 0)
		{
			R_IF |= 4;
			R_TIMA = R_TMA;
		}
	}
}
