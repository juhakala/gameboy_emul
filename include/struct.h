#ifndef STRUCT_H
#define STRUCT_H

//#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
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

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*text_lcd;
	int				*pixel_lcd;
	SDL_Rect		rect_lcd;
}					t_sdl;

typedef struct		s_io_reg
{
	u8 r_p1;	u8 r_sb;	u8 r_sc;	u8 r_div;
	u8 r_tima;	u8 r_tma;	u8 r_tac;	u8 r_if;
	u8 r_nr10;	u8 r_nr11;	u8 r_nr12;	u8 r_nr14;
	u8 r_nr21;	u8 r_nr22;	u8 r_nr24;	u8 r_nr30;
	u8 r_nr31;	u8 r_nr32;	u8 r_nr33;	u8 r_nr41;
	u8 r_nr42;	u8 r_nr43;	u8 r_nr44;	u8 r_nr50;
	u8 r_nr51;	u8 r_nr52;	u8 r_lcdc;	u8 r_stat;
	u8 r_scy;	u8 r_scx;	u8 r_ly;	u8 r_lyc;
	u8 r_dma;	u8 r_bgp;	u8 r_obp0;	u8 r_obp1;
	u8 r_wy;	u8 r_wx;	u8 r_ie;	u8 r_nr13;
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
	u8				boot;
	u8				halt;
	u8				ime;
	u8				keys;
	u8				mbc;
	u8				rom_size;
	u8				cram;
	u8				cram_size;
	u8				ram_size;
	u8				frame;
	u8				rtc[5];
	u8				lcd_mode;

	u16				rom_bank;
	u16				rom_banks;
	u8				wram_bank;
	u8				vram_bank;
	u8				cram_bank;
	u8				cram_banks;
	u8				cram_enable;
	u8				cram_mode;

	u8				wy;
	u8				wyc;
}					t_mem_control;


typedef struct		s_timer
{
	u32				cpu_count;
	u32				lcd_count;
	u32				div_count;
	u32				tima_count;
	u8				tac_enable;
	u8				tac_rate;
}					t_timer;

typedef struct		s_mem
{
	unsigned char	*boot;
	unsigned char	*rom; // done
	unsigned char	*ram; // done
	unsigned char	vram[0x8000]; //done
	unsigned char	wram[0x8000]; //done
	unsigned char	rest_ram[0x2000]; //echo, oam, io_regs, hram
	unsigned char	halt;
	unsigned char	ime;
	
	unsigned int	cycle;
	unsigned int	last_cycle;

	t_reg			*reg;
	t_io_reg		*io_reg;
	t_header		*header;
	t_mem_control	*memory;
	t_timer			*timer;
	t_sdl			*sdl;
	unsigned int	time_old;
	unsigned int	time_new;
	unsigned int	fps;
}					t_mem;

typedef struct		s_op
{
	int				(*f)();
}					t_op;

t_op				g_op_tab[OP_TAB_SIZE];
t_op				g_bit_tab[OP_TAB_SIZE];

int					g_op_size[OP_TAB_SIZE];
int					g_op_cycle[OP_TAB_SIZE];
int					g_cb_cycle[OP_TAB_SIZE];
char				*g_op_str[OP_TAB_SIZE];


#endif
