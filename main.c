//#include "define.h"
//#include "struct.h"
#include "z80.h"

void put_16bits(unsigned short x, unsigned char *addr)
{
	*addr = x >> 8;
	*(addr + 1) = x & 0xFF;
}

unsigned char *read_ram16bits(unsigned char *ram_addr, unsigned char *addr)
{
	unsigned short val;

	val = *addr << 8;
	val += *(addr + 1);
	ram_addr += val;
	return (ram_addr);
}

unsigned short read_16bits(unsigned char *addr)
{
	unsigned short val;

	val = *addr << 8;
	val += *(addr + 1);
	return (val);
}

void	print_rom_mem(t_mem *mem, int size)
{
	unsigned int i = 0;
	unsigned int c = 0;
	
	printf("%05x : ", 0);
	while (i < size)
	{
		printf("%02x", mem->rom[i++]);
		if (i % 2 == 0)
		{
			printf(" ");
			if (i % 8 == 0)
				printf(" ");
		}
		if (i % 16 == 0)
		{
			printf("|");
			while (c < i)
			{
				if (mem->rom[c] > 31 && mem->rom[c] < 127)
					printf("%c", mem->rom[c]);
				else
					printf(".");
				c++;
			}
			if (i + 1 < size)
				printf("|\n%05x : ", i);
			else
				printf("|\n");
		}
	}
	if (i != c)
	{
		while (i++ % 16 != 0)
		{
			printf("  ");
			if (i % 2 == 0)
			{
				printf(" ");
				if (i % 8 == 0)
					printf(" ");
			}
		}
		printf("|");
		while (c < size)
		{
			if (mem->rom[c] > 31 && mem->rom[c] < 127)
				printf("%c", mem->rom[c]);
			else
				printf(".");
			c++;
		}
		printf("|\n");
	}
}

void	print_ram_mem(t_mem *mem, int size)
{
	unsigned int i = 0;
	unsigned int c = 0;
	
	printf("%05x : ", 0);
	while (i < size)
	{
		printf("%02x", mem->ram[i++]);
		if (i % 2 == 0)
		{
			printf(" ");
			if (i % 8 == 0)
				printf(" ");
		}
		if (i % 16 == 0)
		{
			printf("|");
			while (c < i)
			{
				if (mem->ram[c] > 31 && mem->ram[c] < 127)
					printf("%c", mem->ram[c]);
				else
					printf(".");
				c++;
			}
			if (i + 1 < size)
				printf("|\n%05x : ", i);
			else
				printf("|\n");
		}
	}
	if (i != c)
	{
		while (i++ % 16 != 0)
		{
			printf("  ");
			if (i % 2 == 0)
			{
				printf(" ");
				if (i % 8 == 0)
					printf(" ");
			}
		}
		printf("|");
		while (c < size)
		{
			if (mem->ram[c] > 31 && mem->ram[c] < 127)
				printf("%c", mem->ram[c]);
			else
				printf(".");
			c++;
		}
		printf("|\n");
	}
}

int	read_to_mem(char **av, t_mem *mem)
{
	FILE *fp;
	size_t size;

	if (!(fp = fopen(av[1], "r")))
		return (1);
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	mem->rom = (unsigned char*)malloc(sizeof(unsigned char) * size);
	fread(mem->rom, 1, size, fp);
	mem->memory->rom_size = size;
	memcpy(mem->header, &(*(mem->rom + 0x104)), 76);
	fclose(fp);
	return (0);
}

int		check_header_info(t_mem *mem)
{
	if (mem->header->cart_type > 31 || mem->header->rom_size > 6 || mem->header->ram_size > 4)
		return (1);
	int nin_logo[48] = {0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0c, 0x00, 0x0d,
						0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e, 0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99,
						0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e};
	for (int i = 0; i < 48; i++)
	{
		if (mem->header->logo[i] != nin_logo[i])
			return (1);
	}

	unsigned char res = 0;
	for (int i = 0; i + 0x134 < 0x14d; i++)
		res = res - mem->rom[i + 0x134] - 1;
	if (res != mem->header->h_check_sum)
		return (1);

	int mbc_arr[32] = { 0, 1, 1, 1,-1, 2, 2,-1, 0, 0,-1, 0, 0, 0,-1, 3,
						3, 3, 3, 3,-1,-1,-1,-1,-1, 5, 5, 5, 5, 5, 5, 0};
	mem->memory->mbc = mbc_arr[mem->header->cart_type];

	int rom_banks_arr[7] = {2, 4, 8, 16, 32, 64, 128};
	mem->memory->rom_banks = rom_banks_arr[mem->header->rom_size];

	int ram_banks_arr[5] = {0, 1, 1, 4, 16};
	mem->memory->ram_banks = ram_banks_arr[mem->header->ram_size];

	int ram_size_arr[6] = {0, 2048, 8192, 32768, 131072, 65536};
	mem->memory->ram_size = ram_size_arr[mem->header->ram_size];
	return (0);
}

void	power_up(t_mem *mem)
{
	mem->reg->pc = 0;
	int size;
	unsigned char boot[256] = {0x31, 0xfe, 0xff, 0xaf, 0x21, 0xff, 0x9f, 0x32, 0xcb, 0x7c, 0x20, 0xfb, 0x21, 0x26, 0xff, 0x0e,
							   0x11, 0x3e, 0x80, 0x32, 0xe2, 0x0c, 0x3e, 0xf3, 0xe2, 0x32, 0x3e, 0x77, 0x77, 0x3e, 0xfc, 0xe0,
							   0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1a, 0xcd, 0x95, 0x00, 0xcd, 0x96, 0x00, 0x13, 0x7b,
							   0xfe, 0x34, 0x20, 0xf3, 0x11, 0xd8, 0x00, 0x06, 0x08, 0x1a, 0x13, 0x22, 0x23, 0x05, 0x20, 0xf9,
							   0x3e, 0x19, 0xea, 0x10, 0x99, 0x21, 0x2f, 0x99, 0x0e, 0x0c, 0x3d, 0x28, 0x08, 0x32, 0x0d, 0x20,
							   0xf9, 0x2e, 0x0f, 0x18, 0xf3, 0x67, 0x3e, 0x64, 0x57, 0xe0, 0x42, 0x3e, 0x91, 0xe0, 0x40, 0x04,
							   0x1e, 0x02, 0x0e, 0x0c, 0xf0, 0x44, 0xfe, 0x90, 0x20, 0xfa, 0x0d, 0x20, 0xf7, 0x1d, 0x20, 0xf2,
							   0x0e, 0x13, 0x24, 0x7c, 0x1e, 0x83, 0xfe, 0x62, 0x28, 0x06, 0x1e, 0xc1, 0xfe, 0x64, 0x20, 0x06,
							   0x7b, 0xe2, 0x0c, 0x3e, 0x87, 0xe2, 0xf0, 0x42, 0x90, 0xe0, 0x42, 0x15, 0x20, 0xd2, 0x05, 0x20,
							   0x4f, 0x16, 0x20, 0x18, 0xcb, 0x4f, 0x06, 0x04, 0xc5, 0xcb, 0x11, 0x17, 0xc1, 0xcb, 0x11, 0x17,
							   0x05, 0x20, 0xf5, 0x22, 0x23, 0x22, 0x23, 0xc9, 0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b,
							   0x03, 0x73, 0x00, 0x83, 0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e,
							   0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc,
							   0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9, 0x33, 0x3e, 0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c,
							   0x21, 0x04, 0x01, 0x11, 0xa8, 0x00, 0x1a, 0x13, 0xbe, 0x20, 0xfe, 0x23, 0x7d, 0xfe, 0x34, 0x20,
							   0xf5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xfb, 0x86, 0x20, 0xfe, 0x3e, 0x01, 0xe0, 0x50};

	while ((size = read_op_byte(boot, mem)) != -1 && mem->reg->pc < 256)
		mem->reg->pc += size;
		
}

void	map_io_registers(t_mem *mem)
{
	mem->io_reg->ff00 = &mem->ram[0xff00];
}

int		fetch_save(t_mem *mem)
{
//	FILE *fp;
//	char save[260];
	
//	sprintf(save, "pokemone_save_size_%d", mem->memory->ram_size);
	mem->ram = (unsigned char*)malloc(sizeof(unsigned char) * mem->memory->ram_size);
//	fp = fopen(save, "r")
//	if (fp)
//	{
//		fread(mem->ram, 1, mem->memory->ram_size, fp);
//		fclose(fp);
//	}

	bzero(mem->ram, mem->memory->ram_size); //tmp for testing
	map_io_registers(mem);
	return (0);
}

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
	printf("GOT TO END OF PROGRAM!!\n");
	
}

int		main(int ac, char **av)
{
	t_mem *mem;

	mem = (t_mem*)malloc(sizeof(t_mem));
	mem->reg = (t_reg*)malloc(sizeof(t_reg));
	mem->io_reg = (t_io_reg*)malloc(sizeof(t_io_reg));
	mem->header = (t_header*)malloc(sizeof(t_header));
	mem->memory = (t_mem_control*)malloc(sizeof(t_mem_control));
	if (ac > 1)
		read_to_mem(av, mem);
	if (check_header_info(mem))
		return (0);
	if (fetch_save(mem))
		return (0);
	power_up(mem);
	test(mem);
	return (0);
}
