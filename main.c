#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define RW_MEM_SIZE 26
#define RW mem->rw

#define A &mem->rw[0]
#define F &mem->rw[1]
#define B &mem->rw[2]
#define C &mem->rw[3]
#define D &mem->rw[4]
#define E &mem->rw[5]
#define H &mem->rw[6]
#define L &mem->rw[7]

#define I &mem->rw[8]
#define R &mem->rw[9]
#define IX &mem->rw[10]
#define IY &mem->rw[12]
#define SP &mem->rw[14]
#define PC &mem->rw[16]

#define PCV read_16bits(PC)

#define Aalt &mem->rw[18]
#define Falt &mem->rw[19]
#define Balt &mem->rw[20]
#define Calt &mem->rw[21]
#define Dalt &mem->rw[22]
#define Ealt &mem->rw[23]
#define Halt &mem->rw[24]
#define Lalt &mem->rw[25]

/*
** GENERAL purpose registers
** 8 bit
** a = accumulator register
** f = flag's register, [S][Z][X][H][X][P/V][N][C]
**						 0  1  2  3  4   5   6  7
**		sign flag, zero flag, halt carry, parity/overflow, add/sub, carry
** b to l can be paired bc, de, hl to 16 bit register
**
** SPECIAL purpose registers
** 8 bit
** i = interrupt page address
** r = memory refresh
** 16 bit
** ix = index register
** iy = index register
** sp = stack pointer
** pc = program counter
*/

typedef struct		s_mem
{
	unsigned char	rw[RW_MEM_SIZE];
}					t_mem;

short read_16bits(unsigned char *addr)
{
	short val = 0;
	short val1 = 0;

	val = (*addr & 0xFF) << 8;
	val += *(addr + 1) & 0xFF;
	return (val);
}

void print_rw_mem(t_mem *mem)
{
	int i = 0;
	while (i < RW_MEM_SIZE)
	{
		printf("%02x", RW[i++]);
		if (i % 4 == 0)
			printf("\n");
	}
	if (i % 4 != 0)
		printf("\n");
}

void print_reg_mem(t_mem *mem)
{
	printf("%02x %02x %02x %02x\n", *A, *F, *Aalt, *Aalt);
	printf("%02x %02x %02x %02x\n", *B, *C, *Balt, *Calt);
	printf("%02x %02x %02x %02x\n", *D, *E, *Dalt, *Ealt);
	printf("%02x %02x %02x %02x\n", *H, *L, *Halt, *Lalt);
	printf("%02x %02x\n", *I, *R);
	printf("%02x %02x\n", *IX, *(IX + 1));
	printf("%02x %02x\n", *IY, *(IY + 1));
	printf("%02x %02x\n", *SP, *(SP + 1));
	printf("%02x %02x\n", *PC, *(PC + 1));
}

void default_addressies(t_mem *mem)
{
	mem->rw[16] = 1;
	mem->rw[17] = 255;
//	*PC += 2;
//	mem->rw[17] = 15;
//	mem->rw[14] = 10;
//	*PC += 10;
//	*(PC + 1) += 17;
//	*(PCA + 1) += 17;
//	&PC = 1;
}

int main(void)
{
	t_mem *mem;

	mem = (t_mem*)malloc(sizeof(t_mem));
	bzero(RW, RW_MEM_SIZE);
	default_addressies(mem);

	print_reg_mem(mem);
	printf("\n");
	print_rw_mem(mem);
	printf("PC int = '%d'\n", PCV);
	return (0);
}
