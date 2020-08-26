/*
** GENERAL purpose registers
** 8 bit
** a = accumulator register
** f = flag's register, [S][Z][X][H][X][P/V][N][C]
**                       0  1  2  3  4   5   6  7
**      sign flag, zero flag, halt carry, parity/overflow, add/sub, carry
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
	unsigned char	ram[MEM_SIZE];
}					t_mem;
