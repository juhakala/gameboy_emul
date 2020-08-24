#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define RW_MEM_SIZE 208
#define RW mem->rw


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
** 16 bit
** ix = index register
** iy = index register
** sp = stack pointer
** pc = program counter
*/
typedef struct		s_mem
{
	unsigned char	rw[RW_MEM_SIZE];
	int				a;
	int				f;
	int				b;
	int				c;
	int				d;
	int				e;
	int				h;
	int				l;
	int				ix;
	int				iy;
	int				sp;
	int				pc;
}					t_mem;

void print_rw_mem(t_mem *mem)
{
	int i = 0;
	while (i < RW_MEM_SIZE)
	{
		printf("%02x ", RW[i++]);
		if (i % 16 == 0)
			printf("\n");
	}
}

int main(void)
{
	t_mem *mem;

	mem = (t_mem*)malloc(sizeof(t_mem));
	bzero(RW, RW_MEM_SIZE);
	print_rw_mem(mem);
	return (0);
}
