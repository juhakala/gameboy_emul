#include "z80.h"
#include "define.h"

void	test(t_mem *mem)
{
//	print_rom_mem(mem, mem->rom_size);
//	printf("%s\n", mem->header->title);
//	printf("%x\n", mem->header->cart_type);
//	printf("%x\n", mem->header->rom_size);
//	printf("%x\n", mem->header->ram_size);
//	printf("%d\n", mem->memory->rom_size);
//	printf("%d\n", mem->memory->ram_size);
//	*mem->io_reg->ff00 = 255;
//	print_ram_mem(mem, 0xff10);
	printf("LAST read(0x%04hx) = 0x%02hhx\n", mem->reg->pc, read(mem->reg->pc, mem));
	if (read(mem->reg->pc, mem) == 0xcb)
		printf("after cb 0x%02hhx\n", read(mem->reg->pc + 1, mem));
	printf("GOT TO END OF PROGRAM!!\n");
	
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
/*
		if (*mem->io_reg->ff50 != 0) //ff50 = 0 boot rom
		{
			mem->reg->pc += size;
			read_mem_bytes(mem, 1);
			printf(" <- boot rom done\n");
			exit(0);
			}*/
//
		mem->reg->pc += size;
		update_timer(mem);
		update_graphics(mem);
		handle_interrupts(mem);
	}
//	render_lcd(t_mem *mem);
}


int		main(int ac, char **av)
{
	t_mem *mem = NULL;

	if (ac < 2 || !(mem = initial_setup(ac, av)))
		return (0);

//tmp_testing
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
//	test(mem);
//tmp_testing end here
	while (1)
		update_gameboy(mem);
	return (0);
}
