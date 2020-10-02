#include "z80.h"
#include "struct.h"
#include "define.h"

void	handle_interrupts(t_mem *mem)
{
	IME = 0;
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	if (R_IF & R_IE & 1)
	{
		mem->reg->pc = 0x40;
		R_IF ^= 0x1;
	}
	else if (R_IF & R_IE & 2)
	{
		mem->reg->pc = 0x48;
		R_IF ^= 0x2;
	}
	else if (R_IF & R_IE & 4)
	{
		mem->reg->pc = 0x50;
		R_IF ^= 0x4;
	}
	else if (R_IF & R_IE & 8)
	{
		mem->reg->pc = 0x58;
		R_IF ^= 0x8;
	}
	else if (R_IF & R_IE & 0x10)
	{
		mem->reg->pc = 0x60;
		R_IF ^= 0x10;
	}
}
