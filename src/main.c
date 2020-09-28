#include "z80.h"
#include "define.h"

void	check_boot_values(t_mem *mem)
{
	if (mem->reg->a != 0x1)
		printf("1 %02x A\n", mem->reg->a);
	if (mem->reg->f != 0xb0)
		printf("2 %02x F\n", mem->reg->f);
	if (mem->reg->bc != 0x0013)
		printf("3 %04x BC\n", mem->reg->bc);
	if (mem->reg->de != 0x00d8)
		printf("4 %04x DE\n", mem->reg->de);
	if (mem->reg->hl != 0x014d)
		printf("5 %04x HL\n", mem->reg->hl);
	if (mem->reg->sp != 0xfffe)
		printf("6 %04x SP\n", mem->reg->sp);
	if (*mem->io_reg->ff05 != 0x0) //tima
		printf("7 %02x tima\n", *mem->io_reg->ff05);
	if (*mem->io_reg->ff06 != 0x0) //tma
		printf("8 %02x tma\n", *mem->io_reg->ff06);
	if (*mem->io_reg->ff07 != 0x0) //tac
		printf("9 %02x tac\n", *mem->io_reg->ff07);
	if (*mem->io_reg->ff10 != 0x80) //nr10
		printf("10 %02x sound\n", *mem->io_reg->ff10);
	if (*mem->io_reg->ff11 != 0xbf) //nr11
		printf("11 %02x sound\n", *mem->io_reg->ff11);
	if (*mem->io_reg->ff12 != 0xf3) //nr12
		printf("12 %02x\n", *mem->io_reg->ff12);
	if (*mem->io_reg->ff14 != 0xbf) //nr14
		printf("13 %02x sound\n", *mem->io_reg->ff14);
	if (*mem->io_reg->ff16 != 0x3f) //nr21
		printf("14 %02x sound\n", *mem->io_reg->ff16);
	if (*mem->io_reg->ff17 != 0x0) //nr22
		printf("15 %02x\n", *mem->io_reg->ff17);
	if (*mem->io_reg->ff19 != 0xbf) //nr24
		printf("16 %02x sound\n", *mem->io_reg->ff19);
	if (*mem->io_reg->ff1a != 0x7f) //nr30
		printf("17 %02x sound\n", *mem->io_reg->ff1a);
	if (*mem->io_reg->ff1b != 0xff) //nr31
		printf("18 %02x sound\n", *mem->io_reg->ff1b);
	if (*mem->io_reg->ff1c != 0x9f) //nr32
		printf("19 %02x sound\n", *mem->io_reg->ff1c);
	if (*mem->io_reg->ff1e != 0xbf) //nr33
		printf("20 %02x sound\n", *mem->io_reg->ff1e);
	if (*mem->io_reg->ff20 != 0xff) //nr41
		printf("21 %02x sound \n", *mem->io_reg->ff20);
	if (*mem->io_reg->ff21 != 0x00) //nr42
		printf("22 %02x\n", *mem->io_reg->ff21);
	if (*mem->io_reg->ff22 != 0x0) //nr43
		printf("23 %02x\n", *mem->io_reg->ff22);
	if (*mem->io_reg->ff23 != 0xbf) //nr44
		printf("24 %02x sound\n", *mem->io_reg->ff23);
	if (*mem->io_reg->ff24 != 0x77) //nr50
		printf("25 %02x\n", *mem->io_reg->ff24);
	if (*mem->io_reg->ff25 != 0xf3) //nr51
		printf("26 %02x\n", *mem->io_reg->ff25);
	if (*mem->io_reg->ff26 != 0xf1) //nr52
		printf("27 %02x sound on/off\n", *mem->io_reg->ff26);
	if (*mem->io_reg->ff40 != 0x91) //LCDC
		printf("28 %02x\n", *mem->io_reg->ff40);
	if (*mem->io_reg->ff42 != 0x0) //SCY
		printf("29 %02x\n", *mem->io_reg->ff42);
	if (*mem->io_reg->ff43 != 0x0) //SCX
		printf("30 %02x\n", *mem->io_reg->ff43);
	if (*mem->io_reg->ff45 != 0x0) //LYC
		printf("31 %02x\n", *mem->io_reg->ff45);
	if (*mem->io_reg->ff47 != 0xfc) //BGP
		printf("32 %02x\n", *mem->io_reg->ff47);
	if (*mem->io_reg->ff48 != 0xff) //OBP0
		printf("33 %02x color palette 0\n", *mem->io_reg->ff48);
	if (*mem->io_reg->ff49 != 0xff) //OBP1
		printf("34 %02x color palette 1\n", *mem->io_reg->ff49);
	if (*mem->io_reg->ff4a != 0x0) //WY
		printf("35 %02x\n", *mem->io_reg->ff4a);
	if (*mem->io_reg->ff4b != 0x0) //WX
		printf("36 %02x\n", *mem->io_reg->ff4b);
	if (*mem->io_reg->ffff != 0x0) //IE
		printf("37 %02x\n", *mem->io_reg->ffff);
	if (*mem->io_reg->ff50 != 1) //no boot
		printf("38 %02x\n", *mem->io_reg->ff50);
	if (mem->reg->pc != 0x100)
		printf("39 %04x\n", mem->reg->pc);
}

void	update_gameboy(t_mem *mem)
{
	int max_cycles = 69905;
	int size;

	mem->cycle = 0;
	while (mem->cycle < max_cycles)
	{
		while (mem->halt == 1)
		{
//			size = 0;//tmp for now
			//wait for interrupt function here
			printf("at this pont it would wait interrupts, so exit now\n");
			printf("halt = %d\n", mem->halt);
			exit(0);
		}
//		else
			size = read_op_byte(mem);
//
		if (size == -1)// -1 if not implemented yet
		{
			read_mem_bytes(mem, 1);
			printf(" <- not done yet\n");
			exit(0);
		}

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
	if (ac >= 3 && !strcmp(av[2], "count"))
	{
		mem->count = 1;
		int ret;
		for (int i = 0; i < OP_TAB_SIZE; i++)
		{
			mem->cycle = i;
			ret = g_op_tab[i].f(mem);
			if (ac >= 4 && !strcmp(av[3], "empty") && ret == -1)
				printf("%d\n", i);
		}
		for (int i = 0; i < OP_TAB_SIZE; i++)
		{
			mem->cycle = i + 0xff;
			ret = g_bit_tab[i].f(mem);
			if (ac >= 4 && !strcmp(av[3], "empty") && ret == -1)
				printf("%d\n", i + 0xff);
		}
		printf("\n\ndone and to be done %d / %d\n", OP_TAB_SIZE * 2 - mem->not_done, OP_TAB_SIZE * 2);
		return (0);
	}
//tmp_testing end here
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
