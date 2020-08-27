#include "define.h"
#include "struct.h"

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
//	val %= MEM_SIZE; // pc can never be more than 63999 ? so unnecessary ?
	ram_addr += val;
	return (ram_addr);
}

unsigned short read_16bits(unsigned char *addr)
{
	unsigned short val;

	val = *addr << 8;
	val += *(addr + 1);
//	val %= MEM_SIZE; // pc can never be more than 63999 ? so unnecessary ?
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
	printf("SP  %02x %02x\n", *SP, *(SP + 1));
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

int main(void)
{
	t_mem *mem;

	mem = (t_mem*)malloc(sizeof(t_mem));
	bzero(RW, RW_MEM_SIZE);
	bzero(RAM, MEM_SIZE);
	ram_rw_testing(mem);
	print_reg_mem(mem); // print register values in %02x
	printf("\n");
	print_rw_mem(mem); // print all 208 bits from rw memory block
	printf("\n");
	printf("PC uint = '%u'\n", PC); // value of pc
	printf("RAM[0] address = '%p'\n", &RAM[0]); // address of &ram[0] + pc value
	printf("RAM[PC] address = '%p'\n", PCR); // address of &ram[0] + pc value
	printf("*RAM[PC] = '%d'\n", *PCR);
	printf("PC uint = '%u'\n", PC); // 0x0107 =  263
	printf(" = '%u'\n", mem->ram[263]);
	PCP(10000);
	printf("PC uint = '%u'\n", PC);
	PCP(53736); // to 63999
	printf("PC uint = '%u'\n", PC);
	print_reg_mem(mem); // print register values in %02x
	PCP(2); // (63999 + 2) % MEM_SIZE = 1
	printf("PC uint = '%u'\n", PC);
	print_reg_mem(mem); // print register values in %02x
//	system("leaks a.out");
	return (0);
}
