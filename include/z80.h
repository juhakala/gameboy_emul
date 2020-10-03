#ifndef Z80_H
#define Z80_H

#include "../SDL2-2.0.12/include/SDL.h" 
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
void			print_f_flag(unsigned char c, t_mem *mem); //tmp
	
// timer.c
void			set_timer_counter(t_mem *mem);
void			update_timer(t_mem *mem);

// interrupts.c
void			reguest_interrupt(int bit, t_mem *mem);
void			handle_interrupts(t_mem *mem);

// lcd.c
int				update_graphics(t_mem *mem);

// sdl.c
void			render_sdl(t_mem *mem);
int				init_sdl(t_mem *mem);

#endif
