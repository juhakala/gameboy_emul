//#include "op.h"
//#include "struct.h"
#include "z80.h"

int	op_nop(t_mem *mem)
{
	if (PRINT)
		read_mem_bytes(mem, 1);
	CYCLE += 1;
	PC_ADD(1);
	return (0);
}
