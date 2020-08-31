#include "z80.h"

int	max_not_done(t_mem *mem)
{
	printf("	start_point 0x%05hx ", PC);
	return (-1);
}
int	not_done(t_mem *mem)
{
	printf("not done yet : RAM[PC](%x, %d), PC(%hx), ", RAM[PC], RAM[PC], PC);
	read_mem_bytes(mem, 1);
	exit(0);
//	printf("\n\n");
	return (-1);
}
