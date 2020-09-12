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

int		main(int ac, char **av)
{
	t_mem *mem = NULL;

	if (!(mem = initial_setup(ac, av)))
		return (0);

//tmp_testing
	if (ac >= 3 && !strcmp(av[2], "count"))
	{
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
		printf("\n\ndone and to be done %d / %d\n", OP_TAB_SIZE * 2 - mem->not_done, OP_TAB_SIZE * 2 - 12);
		return (0);
	}

	int size;
	while ((size = read_op_byte(mem)) != -1 && *mem->io_reg->ff50 == 0)
	{
		mem->reg->pc += size;
//		printf("here\n %d, %d, %d\n", *mem->io_reg->ff50, size, mem->reg->pc);
	}
	test(mem);
//tmp_testing end here

//	run_gameboy(mem);
	
	return (0);
}
