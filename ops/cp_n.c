#include "z80.h"
#include "op.h"

int	op_cp_n(t_mem *mem)
{
	RAM[PC + 1] = 0x11;
	if (PRINT)
		read_mem_bytes(mem, 2);
	CYCLE += 2;
	PC_ADD(1);
	for (int x = 7; x > -1; x--)
	{
		printf("%d", CHECK_FLAG(x));
	}
	printf("\nSZxHxPAC\n\n");
//set correstponding bit with 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128;
//                            c   a   p   x    h    x    z     s
	*F =
		(*A < RAM[PC]) | 							// carry set if borrow
		2 | 											// add/sub set to sub
		((char)*A - (char)RAM[PC] < -127 ? 4 : 0) | // parity/overflow set if overflow or reset 
		0 |  											// not used x
		((*A ^ RAM[PC] ^ ((char)*A - (char)RAM[PC])) & 16) | // half borrow
		0 |   											// not used x
		(*A - RAM[PC + 1] == 0 ? 64 : 0) |				//set zero flag if == 0 or reset
		(((char)*A - (char)RAM[PC]) & 128);			//set sign flag if < 0 or reset
	for (int x = 7; x > -1; x--)
	{
		printf("%d", CHECK_FLAG(x));
	}
	printf("\nSZxHxPAC\n");
	*F = 
		eight_bit(*A, RAM[PC]) |
		seven_bit(*A, RAM[PC]) |
		// x not used
		five_bit(*A, RAM[PC]) |
		// x not used
		three_bit(*A, RAM[PC], '-') |
		2 | // add = 0 / sub = 1
		one_bit(*A, RAM[PC]);
		
	for (int x = 7; x > -1; x--)
	{
		printf("%d", CHECK_FLAG(x));
	}
	printf("\nSZxHxPAC\n");
	PC_ADD(1);
	return (0);
}
