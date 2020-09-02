#include "z80.h"

int	op_rst_p(t_mem *mem)
{
	int res = 0;

	if (PRINT)
		read_mem_bytes(mem, 2);
	CYCLE += 3;
	RAM[PC] = 0;
	RAM[PC] |= (1 << 3);
	RAM[PC] |= (1 << 4);
	RAM[PC] |= (1 << 5);
//	res += ((RAM[PC] >> 3) & 0x01) == 1 ? 0x08 : 0;
//	res += ((RAM[PC] >> 4) & 0x01) == 1 ? 0x10 : 0;
//	res += ((RAM[PC] >> 5) & 0x01) == 1 ? 0x20 : 0;
	SP_ADD(-1);
	RAM[SP] = *PCA;
	SP_ADD(-1);
	RAM[SP] = *(PCA + 1);
	PC_PUT(0x00 + res);
	printf("short pc = %hx\n", PC);
//	printf("PC = %d, %x\n", PC, PC);
//	printf("RAM[PC + 1] = %d, pc->%d\n", RAMI(PC + 1), (unsigned short)(PC + 1));
	printf("RAM[PC + 1] = %d, pc->%d\n", RAM[(PC + 1) % MEM_SIZE], (unsigned short)(PC + 1));
	printf("RAM[PC + 1] = %d, pc->%d\n", RAM[(PC) % MEM_SIZE], (unsigned short)(PC));
	PC_ADD(-1);
	printf("RAM1[pc] = %d, %d\n", RAMI(PC + 1), PC + 1);
	PC_ADD(1);
	printf("%d, %d, %d\n", (PC + 1) % MEM_SIZE, PC, 0xFFFF);
	printf("%ld, %lld, %d\n", 2L, 2LL, 2);
	return (0);
}
