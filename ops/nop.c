#include "z80.h"
#include "struct.h"
#include "define.h"

static void	printing(t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, 1);
	if (PRINT & 2)
		printf("	NOP");
	printf("\n");
}

int	op_nop(t_mem *mem)
{
	if (PRINT)
		printing(mem);
	CYCLE += 1;
	return (1);
}
