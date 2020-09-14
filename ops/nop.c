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
// 0x00
int	op_nop(t_mem *mem)
{
	if (PRINT)
		printing(mem);
	CYCLE += 1;
	return (1);
}
// 0xd3 0xdb 0xdd 0xe3 0xe4 0xeb 0xe 0xed 0xf4 0xfc 0xfd
int	empty(t_mem *mem)
{
	if (PRINT)
		printf("HIT EMPTY instruction!!\n");
	if (mem->count != 1)
		exit(0);
	return (0);
}
	
