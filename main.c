#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define RW_MEM_SIZE 26
#define RW mem->rw

#define A *mem->a[0]
#define F *mem->f[0]
#define B *mem->b[0]
#define C *mem->c[0]
#define D *mem->d[0]
#define E *mem->e[0]
#define H *mem->h[0]
#define L *mem->l[0]

#define I *mem->i
#define R *mem->r
#define IX *mem->ix
#define IY *mem->iy
#define SP *mem->sp
#define PC *mem->pc

#define PCC(x) mem->rw[16 + x]

#define Aalt *mem->a[1]
#define Falt *mem->f[1]
#define Balt *mem->b[1]
#define Calt *mem->c[1]
#define Dalt *mem->d[1]
#define Ealt *mem->e[1]
#define Halt *mem->h[1]
#define Lalt *mem->l[1]
/*
** GENERAL purpose registers
** 8 bit
** a = accumulator register
** f = flag's register, [S][Z][X][H][X][P/V][N][C]
**						 0  1  2  3  4   5   6  7
**		sign flag, zero flag, halt carry, parity/overflow, add/sub, carry
** b - l
** can be paired bc, de, hl to 16 bit register
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
	unsigned char	*a[2];
	unsigned char	*f[2];
	unsigned char	*b[2];
	unsigned char	*c[2];
	unsigned char	*d[2];
	unsigned char	*e[2];
	unsigned char	*h[2];
	unsigned char	*l[2];
	unsigned char	*i;
	unsigned char	*r;
	unsigned char	*ix;
	unsigned char	*iy;
	unsigned char	*sp;
	unsigned char	*pc;
}					t_mem;

void print_rw_mem(t_mem *mem)
{
	int i = 0;
	while (i < RW_MEM_SIZE)
	{
		printf("%02x ", RW[i++]);
		if (i % 2 == 0)
			printf("\n");
	}
}

void print_reg_mem(t_mem *mem)
{
	printf("%02x %02x %02x %02x\n", A, F, Aalt, Aalt);
	printf("%02x %02x %02x %02x\n", B, C, Balt, Calt);
	printf("%02x %02x %02x %02x\n", D, E, Dalt, Ealt);
	printf("%02x %02x %02x %02x\n", H, L, Halt, Lalt);
	printf("%02x %02x\n", I, R);
	printf("%02x %02x\n", IX, *(&IX + 1));
	printf("%02x %02x\n", IY, *(&IY + 1));
	printf("%02x %02x\n", SP, *(&SP + 1));
	printf("%02x %02x\n", PC, *(&PC + 1));
	printf("%02x %02x\n", PCC(0), PCC(1));
}

void default_addressies(t_mem *mem)
{
	//general purpose
	mem->a[0] = &mem->rw[0];
	mem->f[0] = &mem->rw[1];
	mem->b[0] = &mem->rw[2];
	mem->c[0] = &mem->rw[3];
	mem->d[0] = &mem->rw[4];
	mem->e[0] = &mem->rw[5];
	mem->h[0] = &mem->rw[6];
	mem->l[0] = &mem->rw[7];
	//special purpose
	mem->i = &mem->rw[8];
	mem->r = &mem->rw[9];
	mem->ix = &mem->rw[10];
	mem->iy = &mem->rw[12];
	mem->sp = &mem->rw[14];
	mem->pc = &mem->rw[16];
	//altered general purpose
	mem->a[1] = &mem->rw[18];
	mem->f[1] = &mem->rw[19];
	mem->b[1] = &mem->rw[20];
	mem->c[1] = &mem->rw[21];
	mem->d[1] = &mem->rw[22];
	mem->e[1] = &mem->rw[23];
	mem->h[1] = &mem->rw[24];
	mem->l[1] = &mem->rw[25];
	//	mem->a[1] = &mem->rw[1];
//	*mem->a[0] = '1';
//	*mem->pc = 'f';
	mem->rw[17] = 'f';
}

int main(void)
{
	t_mem *mem;

	mem = (t_mem*)malloc(sizeof(t_mem));
	bzero(RW, RW_MEM_SIZE);
//	print_rw_mem(mem);
	default_addressies(mem);
//	printf("\n");
//	print_rw_mem(mem);
//	printf("\n");
	print_reg_mem(mem);
	return (0);
}
