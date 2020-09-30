#include "z80.h"
#include "define.h"

void	debug_print(t_mem *mem)
{
//	printf("last cycles = %d\n", mem->last_cycle);
//	printf("total cycles = %d\n", mem->over_all_cycle);
	printf("op in pc = %02x\n", read(mem->reg->pc, mem));
	printf("re pc = %04hx\n", mem->reg->pc);
	printf("re sp = %04hx\n", mem->reg->sp);
	printf("reg A = %02hhx\n", mem->reg->a);
	printf("reg F = %02hhx\n", mem->reg->f);
	printf("reg B = %02x\n", (mem->reg->bc >> 8) & 0xff);
	printf("reg C = %02x\n", mem->reg->bc & 0xff);
	printf("reg D = %02x\n", (mem->reg->de >> 8) & 0xff);
	printf("reg E = %02x\n", mem->reg->de & 0xff);
	printf("reg H = %02x\n", (mem->reg->hl >> 8) & 0xff);
	printf("reg L = %02x\n", mem->reg->hl & 0xff);
	printf("reg ff44 = %02x\n", *mem->io_reg->ff44);
//	printf("SP: %04hx PC: %04hx ", mem->reg->sp, mem->reg->pc);
//	printf("AF:%02hhx%02hhx BC:%04hx DE:%04hx HL:%04hx\n", mem->reg->a, mem->reg->f, mem->reg->bc, mem->reg->de, mem->reg->hl);
}


void	update_gameboy(t_mem *mem)
{
	int max_cycles = 69905;
	int size;

	static int ture = 0;
	mem->cycle = 0;
	while (mem->cycle < max_cycles)
	{
		while (mem->halt == 1)
			mem->halt = 0;
		size = read_op_byte(mem);

/*		if (*mem->io_reg->ff50 != 0) //ff50 = 0 boot rom
		{
			mem->reg->pc += size;
			read_mem_bytes(mem, 1);
			printf(" <- boot rom done\n");
			check_boot_values(mem);
			exit(0);
			}*/
//
		mem->reg->pc += size;
		update_timer(mem);
		update_graphics(mem);
		handle_interrupts(mem);
	}
	render_sdl(mem);
}


int		main(int ac, char **av)
{
	t_mem *mem = NULL;

	if (ac < 2 || !(mem = initial_setup(ac, av)))
		return (0);
//tmp_testing
	if (ac == 3 && !strcmp(av[2], "dump"))
	{
		print_rom_mem(mem, 0xfffff);
		exit(0);
	}
//tmp_testing end here
//	mem->reg->a = 0;
//	mem->reg->f = 0;
//	mem->reg->bc = 0;
//	mem->reg->de = 0;
//	mem->reg->hl = 0;
//	mem->reg->sp = 0;
//	mem->reg->pc = 0;
//	*mem->io_reg->ff44 = 0;
	while (1)
	{
//		*mem->io_reg->ff50 = 1;
		unsigned val;
		mem->time_old = SDL_GetTicks();
		update_gameboy(mem);
		mem->time_new = SDL_GetTicks();
		SDL_Delay((val = 16 - ((val = mem->time_new - mem->time_old) < 16 ? val : 16)));
		mem->time_new = SDL_GetTicks();
		mem->fps = 1000 /(mem->time_new - mem->time_old != 0 ? mem->time_new - mem->time_old : 1);
	}
	return (0);
}
