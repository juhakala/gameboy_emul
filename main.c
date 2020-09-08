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

void print_rw_mem(t_mem *mem)
{
	int i = 0;
	while (i < RW_MEM_SIZE)
	{
		printf("%02x", RW[i++]);
		if (i % 4 == 0)
			printf("\n");
	}
	if (i % 4 != 0)
		printf("\n");
	i = 0;
	while (i < 20)
		printf("%02x ", RAM[i++]);
	printf("\n");
	printf("'%p'\n", &RAM[0]);
	printf("'%p'\n", &RAM[1]);
}

void print_reg_mem(t_mem *mem)
{
	printf("A F %02x %02x\n", *A, *F);
	printf("B C %02x %02x\n", *B, *C);
	printf("D E %02x %02x\n", *D, *E);
	printf("H L %02x %02x\n", *H, *L);
	printf("I R %02x %02x\n", *I, *R);
	printf("IX  %02x %02x\n", *IX, *(IX + 1));
	printf("IY  %02x %02x\n", *IY, *(IY + 1));
	printf("SP  %02x %02x\n", *SPA, *(SPA + 1));
	printf("PC  %02x %02x\n", *PCA, *(PCA + 1));
	printf("Aalt Falt %02x %02x\n", *Aalt, *Aalt);
	printf("Balt Calt %02x %02x\n", *Balt, *Calt);
	printf("Dalt Ealt %02x %02x\n", *Dalt, *Ealt);
	printf("Halt Lalt %02x %02x\n", *Halt, *Lalt);
}

void ram_rw_testing(t_mem *mem)
{
	int i = 0;

	while (i < MEM_SIZE)
	{
		RAM[i] = i;
		i++;
	}
	RW[16] += 0x01;
	RW[17] += 7;
}

void	print_ram_mem(t_mem *mem, int size)
{
	unsigned int i = 0;
	unsigned int c = 0;
	
	printf("%05x : ", 0);
	while (i < size)
	{
		printf("%02x", RAM[i++]);
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
				if (RAM[c] > 31 && RAM[c] < 127)
					printf("%c", RAM[c]);
				else
					printf(".");
				c++;
			}
			printf("|\n%05x : ", i);
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
			if (RAM[c] > 31 && RAM[c] < 127)
				printf("%c", RAM[c]);
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
	while ((size = fread(PCR, 1, BUF_SIZE, fp)))// && PC < MEM_SIZE)
	{
		if (PC + size >= MEM_SIZE)
			break ;
		PC_ADD(size);
	}

	return (0);
}

#include "op.h"

int main(int ac, char **av)
{
	t_mem *mem;

	mem = (t_mem*)malloc(sizeof(t_mem));
	bzero(RW, RW_MEM_SIZE);
	bzero(RAM, MEM_SIZE);

//	print_ram_mem(mem, MEM_SIZE);
//	exit(0);
	if (ac == 2 && !strcmp(av[1], "not_done"))
	{
		mem->not_done = 0;
		for (int i = 0; i < OP_TAB_SIZE; i++)
			g_op_tab[i].f(mem);
		printf("\nNOT_DONE_COUNT = '%d', '%x'\n", mem->not_done, mem->not_done);
	}
	else if (ac >= 2 && !read_to_mem(av, mem))
	{
//	print_ram_mem(mem, MEM_SIZE);
//	exit(0);
		printf("0x147 = %d, %x\n", RAM[0x147], RAM[0x147]);
		printf("0x147 = %d, %x\n", RAM[0x148], RAM[0x148]);
		exit(0);
		PC_PUT(START_POINT);
		CYCLE = 0;
		printf("max op_size = %x, %d\n", OP_TAB_SIZE, g_op_tab[OP_TAB_SIZE - 1].f(mem));
		int size;
		while ((size = read_op_byte(mem)) != -1)
		{
//			read_mem_bytes(mem, size);
//			PC_ADD(size);
		}
		printf("Did not understand: ");
		read_mem_bytes(mem, 1);
	}
	else
		printf("	ac != 2 or av[1] : '%s' could not be opened!\n", av[1]);
//	system("leaks a.out");
	return (0);
}
