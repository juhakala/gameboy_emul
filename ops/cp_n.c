#include "z80.h"

int	op_cp_n(t_mem *mem)
{
	if (PRINT)
		read_mem_bytes(mem, 2);
	CYCLE += 2;
	SET_N_FLAG;
	if (*A - RAM[PC + 1] < 0)
		SET_S_FLAG;
	else
		CLEAR_S_FLAG;
	if (*A == RAM[PC + 1])
		SET_Z_FLAG;
	else
		CLEAR_Z_FLAG;
//	printf("A '%d' == '%d' byte\n", (char)(*A), (char)(RAM[PC + 1]));
	if ((char)*A - (char)RAM[PC + 1] < -127)
		SET_PV_FLAG;
	else
		CLEAR_PV_FLAG;
//	if (*A ^ RAM[PC] ^ (*A - RAM[PC])
//	printf("half-borrow = '%d'\n", (*A ^ RAM[PC + 1] ^ ((char)*A - (char)RAM[PC + 1])) & 16);
//	printf("half-borrow = '%d'\n", -105 & 16);
//	*A = 0xff;
//	printf("A '%d' == '%d' byte\n", (char)(*A), (int)(RAM[PC + 1]));
//	printf("A '%d' == '%d' byte\n", *A, RAM[PC + 1]);
//	*A = -111;
///	printf("pari = %d\n", ((char)*A - (char)RAM[PC + 1] < -127) ? 4 : 0);
//	printf("pari = %d\n", ((char)*A - (char)RAM[PC + 1]));
	for (int x = 7; x > -1; x--)
	{
		printf("%d", CHECK_FLAG(x));
	}
	printf("\nSZxHxPAC\n\n");
//	printf("less = %d\n\n", *A < RAM[PC + 1]);
//	printf("less = %d\n\n", *A > RAM[PC + 1]);
//	printf("yf %d | %d xf = %d\n", 32, 8, 32 | 8);
//	printf("value | 40 = %d\n", RAM[PC] | 40);
//	printf("%d - %d\n", (char)*A, (char)RAM[PC + 1]);
//	printf("%d - %d\n", *A, RAM[PC + 1]);
//	printf("t value %d\n", ((char)*A - (char)RAM[PC + 1]) & 128);

//set correstponding bit with 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128;
//                            c   a   p   x    h    x    z     s
	*F =
		(*A < RAM[PC + 1]) | 							// carry set if borrow
		2 | 											// add/sub set to sub
		((char)*A - (char)RAM[PC + 1] < -127 ? 4 : 0) | // parity/overflow set if overflow or reset 
		0 |  											// not used x
		((*A ^ RAM[PC + 1] ^ ((char)*A - (char)RAM[PC + 1])) & 16) | // half borrow
		0 |   											// not used x
		(*A - RAM[PC + 1] == 0 ? 64 : 0) |				//set zero flag if == 0 or reset
		(((char)*A - (char)RAM[PC + 1]) & 128);			//set sign flag if < 0 or reset
	for (int x = 7; x > -1; x--)
	{
		printf("%d", CHECK_FLAG(x));
	}
	printf("\nSZxHxPAC\n");
	exit(0);
	return (0);
}
