#ifndef OP_H
#define OP_H

//#include "define.h"
#include "z80.h"
//#include "struct.h"

int		max_not_done(t_mem *mem);
int		not_done(unsigned char *memory, t_mem *mem);

int		ld_sp_d16(unsigned char *memory, t_mem *mem);

/*
** ops/utils.c
*/
int		one_bit(char a, char b);
int		three_bit(char a, char b, char c);
int		five_bit(char a, char b);
int		seven_bit(char a, char b);
int		eight_bit(char a, char b);

/*
** ops*.c
*/
int		op_nop(t_mem *mem); // 0x00
int		op_jp_nn(t_mem *mem); // 0xc3
int		op_cp_n(t_mem *mem); //0xfe
int		op_rst_p(t_mem *mem); //0xff

#endif
