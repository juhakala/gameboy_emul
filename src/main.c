#include "z80.h"
#include "define.h"

void	debug_print(t_mem *mem)
{
	printf("op in pc = %02x\n", read(PC, mem));
	printf("re pc = %04hx\n", PC);
	printf("re sp = %04hx\n", R_SP);
	printf("reg A = %02hhx\n", R_A);
	printf("reg F = %02hhx\n", R_F);
	printf("reg B = %02x\n", (R_BC >> 8) & 0xff);
	printf("reg C = %02x\n", R_BC & 0xff);
	printf("reg D = %02x\n", (R_DE >> 8) & 0xff);
	printf("reg E = %02x\n", R_DE & 0xff);
	printf("reg H = %02x\n", (R_HL >> 8) & 0xff);
	printf("reg L = %02x\n", R_HL & 0xff);
}

void	debug_check(t_mem *mem)
{
	static int addr = 0x100;
	static char choose[5] = "addr";

	if (!strcmp(choose, "step"))
		addr--;
	if ((addr < 1 && !strcmp(choose, "step")) || (mem->reg->pc == addr && !strcmp(choose, "addr")))
	{
		debug_print(mem);
		scanf("%s", choose);
		if (!strcmp(choose, "addr"))
			scanf("%x", &addr);
		else
			scanf("%d", &addr);
		printf("%s\n", choose);
	}
}


void	update_gameboy(t_mem *mem)
{
	int size;
	
	int frame = 1;
	while (frame)
	{
		debug_check(mem);
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
		return (0);
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
