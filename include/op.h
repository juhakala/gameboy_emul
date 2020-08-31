#ifndef OP_H
#define OP_H

//#include "define.h"
#include "z80.h"
//#include "struct.h"

int		max_not_done(t_mem *mem);
int		not_done(t_mem *mem);

/*
** ops*.c
*/
int		op_nop(t_mem *mem); // 0x00
int		op_jp_nn(t_mem *mem); // 0xc3
int		op_cp_n(t_mem *mem); //0xfe

#endif
