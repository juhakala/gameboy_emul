#ifndef Z80_H
#define Z80_H

#include "define.h"
#include "struct.h"

/*
** prototypes:
*/
// main.c
void	put_16bits(unsigned short x, unsigned char *addr);
unsigned char *read_ram16bits(unsigned char *ram_addr, unsigned char *addr);
unsigned short read_16bits(unsigned char *addr);

// read.c
t_op	g_op_tab[OP_TAB_SIZE];
int		read_op_byte(t_mem *mem);
void	read_mem_bytes(t_mem *mem, int size);

#endif
