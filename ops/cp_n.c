#include "z80.h"
#include "op.h"

int	op_cp_n(t_mem *mem)
{
	RAM[PC + 1] = 0x11;
	if (PRINT)
		read_mem_bytes(mem, 2);
	CYCLE += 2;
	PC_ADD(1);
	*F = 
		eight_bit(*A, RAM[PC]) |
		seven_bit(*A, RAM[PC]) |
		// x not used
		five_bit(*A, RAM[PC]) |
		// x not used
		three_bit(*A, RAM[PC], '-') |
		2 | // add = 0 / sub = 1
		one_bit(*A, RAM[PC]);
	PC_ADD(1);
	return (0);
}
