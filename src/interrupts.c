#include "z80.h"
#include "struct.h"
#include "define.h"

void	do_interrupt(int interrupt, t_mem *mem)
{
	mem->master_interrupt = 0;
	CLEAR_BIT(interrupt, *mem->io_reg->ff0f);
	
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	if (interrupt == 0)
		mem->reg->pc = 0x40;
	else if (interrupt == 1)
		mem->reg->pc = 0x48;
	else if (interrupt == 2)
		mem->reg->pc = 0x50;
	else if (interrupt == 4)
	mem->reg->pc = 0x60;
}

void	handle_interrupts(t_mem *mem)
{
	if (mem->master_interrupt == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (CHECK_BIT(i, *mem->io_reg->ff0f) == 1)
			{
				if (CHECK_BIT(i, *mem->io_reg->ffff) == 1)
					do_interrupt(i, mem);
			}
		}
	}
}
