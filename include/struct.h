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

#include "define.h"

typedef struct		s_io_reg
{
	unsigned char	*ff00; //p1
	
}					t_io_reg;

typedef struct		s_reg
{
	unsigned char	a;
	unsigned char	f;
	unsigned short	bc;
	unsigned short	de;
	unsigned short	hl;
	unsigned short	pc;
	unsigned short	sp;	
}					t_reg;

typedef struct		s_header
{
	unsigned char	logo[48];
	unsigned char	title[18]; //145
	unsigned char	sgb_flag; //146
	unsigned char	cart_type; //147
	unsigned char	rom_size; //148
	unsigned char	ram_size; //149
	unsigned char	dest_code; //14a
	unsigned char	license_code; //14b
	unsigned char	vres_num; //14c
	unsigned char	h_check_sum; //14d
	unsigned char	g_check_sum[2]; //14f
}					t_header;

typedef struct		s_mqem_control
{
	int				mbc;
	int				rom_size;
	int				ram_size;
	int				rom_banks;
	int				ram_banks;
	
}					t_mem_control;

typedef struct		s_mem
{
	unsigned char	*rom;
	unsigned char	*ram;
	
	unsigned int	cycle;
	int	not_done; //temp for checking

	t_reg			*reg;
	t_io_reg		*io_reg;
	t_header		*header;
	t_mem_control	*memory;
}					t_mem;

typedef struct		s_op
{
	int				(*f)();
}					t_op;
