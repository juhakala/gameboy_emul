#ifndef STRUCT_H
#define STRUCT_H

/*
** GENERAL purpose registers
** 8 bit
** a = accumulator register
** f = flag's register, [Z][N][H][C][x][x][x][x]
**                       7  6  5  4  3  2  1  0
**      zero , sub/add , half carry, carry
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
	unsigned char	*ff00; //p1			r/w
	unsigned char	*ff01; //sb			r/w
	unsigned char	*ff02; //sc			r/w
	unsigned char	*ff04; //div		r/w
	unsigned char	*ff05; //tima		r/w
	unsigned char	*ff06; //tma		r/w
	unsigned char	*ff07; //tac		r/w
	unsigned char	*ff0f; //if			r/w
	unsigned char	*ff10; //nr10		r/w
	unsigned char	*ff11; //nr11		r/w
	unsigned char	*ff12; //nr12		r/w
	unsigned char	*ff13; //nr13		w
	unsigned char	*ff14; //nr14		r/w
	unsigned char	*ff16; //nr21		r/w
	unsigned char	*ff17; //nr22		r/w
	unsigned char	*ff18; //nr23		w
	unsigned char	*ff19; //nr24		r/w
	unsigned char	*ff1a; //nr30		r/w
	unsigned char	*ff1b; //nr31		r/w
	unsigned char	*ff1c; //nr32		r/w
	unsigned char	*ff1d; //nr33		w
	unsigned char	*ff1e; //nr34		r/w
	unsigned char	*ff20; //nr41		r/w
	unsigned char	*ff21; //nr42		r/w
	unsigned char	*ff22; //nr43		r/w
	unsigned char	*ff23; //nr44		r/w
	unsigned char	*ff24; //nr50		r/w
	unsigned char	*ff25; //nr51		r/w
	unsigned char	*ff26; //nr52		r/w			at reset = 0xf1
	unsigned char	*ff30; //wave pattern ram 30 -> 3f
	unsigned char	*ff40; //LCDL		r/w			at reset = 0x91
	unsigned char	*ff41; //STAT		r/w
	unsigned char	*ff42; //SCY		r/w
	unsigned char	*ff43; //SCX		r/w
	unsigned char	*ff44; //LY			r
	unsigned char	*ff45; //LYC		r/w
	unsigned char	*ff46; //DMA		w
	unsigned char	*ff47; //BGP		r/w
	unsigned char	*ff48; //OBPO		r/w
	unsigned char	*ff49; //OBP1		r/w
	unsigned char	*ff4a; //WY			r/w
	unsigned char	*ff4b; //WX			r/w
	unsigned char	*ff50; //boot lock	r/w

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

typedef struct		s_mem_control
{
	int				mbc;
	int				rom_size;
	int				ram_size;
	int				rom_banks;
	int				ram_banks;
	// controls
	unsigned int	ram_enable;
	unsigned int	rom_ram_mode;
	unsigned int	rom_bank;
	unsigned int	ram_bank;


}					t_mem_control;

typedef struct		s_mem
{
	unsigned char	*boot;
	unsigned char	*rom; // done
	unsigned char	*ram; // done
	unsigned char	vram[0x8000]; //done
	unsigned char	wram[0x8000]; //done
	unsigned char	eram[0x1e00]; //done
	unsigned char	oam[0xa0];	//done
	unsigned char	i_o_registers[0x80]; //done
	unsigned char	hram[0x80]; //done
	unsigned char	interrupts; //done
	
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

t_op				g_op_tab[OP_TAB_SIZE];
t_op				g_bit_tab[OP_TAB_SIZE];


#endif
