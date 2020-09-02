#include "z80.h"

int	op_jp_nn(t_mem *mem)
{
	short res;

	if (PRINT)
		read_mem_bytes(mem, 3);
	CYCLE += 3;
	PC_ADD(1);
	res = RAM[PC];
	PC_ADD(1);
	res += RAM[PC] << 8;
//	printf("res = %hd, %hx\n", res, res);
	PC_PUT(res);
	return (0);
}
