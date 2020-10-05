#include "z80.h"
#include "define.h"

void	update_gameboy(t_mem *mem)
{
	int size;
	
	int frame = 1;
	while (frame)
	{
		debug_main(mem);
		if ((HALT || IME) && (R_IF & R_IE & 0x1f))
		{
			HALT = 0;
			if (IME)
				handle_interrupts(mem);
			mem->last_cycle = 4;
		}
		else
		{
			size = read_op_byte(mem);
			PC += size;
		}
		mem->timer->cpu_count += mem->last_cycle;
		frame = update_graphics(mem);
		update_timer(mem);
	}
	render_sdl(mem);
}


int		main(int ac, char **av)
{
	t_mem *mem = NULL;
	unsigned val;

	if (ac < 2 || !(mem = initial_setup(ac, av)))
	{
		printf("./gameboy [rom]\n./gameboy [rom] [no_boot] for not bootstrap\n");
		printf("change PRINT in include/define.h to 1, 2 or 3 to see cycles in standard output\n");
		return (0);
	}
//tmp_testing
	if (ac == 3 && !strcmp(av[2], "dump"))
	{
		print_rom_mem(mem, 0xfffff);
		exit(0);
	}
//
	while (1)
	{
		mem->time_old = SDL_GetTicks();
		update_gameboy(mem);
		mem->time_new = SDL_GetTicks();
		SDL_Delay((val = 16 - ((val = mem->time_new - mem->time_old) < 16 ? val : 16)));
		mem->time_new = SDL_GetTicks();
		mem->fps = 1000 /(mem->time_new - mem->time_old != 0 ? mem->time_new - mem->time_old : 1);
	}
	return (0);
}
