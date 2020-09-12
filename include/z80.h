#ifndef Z80_H
#define Z80_H
 
#include "struct.h"

/*
** prototypes:
*/

// initial_setup.c
t_mem			*initial_setup(int ac, char **av);

// read.c
int				read_op_byte(t_mem *mem);
void			read_mem_bytes(t_mem *mem, int size);

// mbc_read_write.c
int				write(unsigned short addr, unsigned char content, t_mem *mem);
unsigned char	read(unsigned short addr, t_mem *mem);

// hexdumps.c
void			print_rom_mem(t_mem *mem, int size); //tmp
void			print_ram_mem(t_mem *mem, int size); //tmp
	

#endif
