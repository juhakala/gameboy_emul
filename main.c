#include "define.h"
#include "struct.h"

int read_ram16bits(unsigned char *ram_addr, unsigned char *addr)
{
	int val;

	val = *addr << 8;
	val += *(addr + 1);
//	val += ram
	printf("addr = %p\n", ram_addr);
	ram_addr += val;
	printf("addr = %p\n", ram_addr);
	return (val);
}

short read_16bits(unsigned char *addr)
{
	short val;

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
	printf("%02x %02x %02x %02x\n", *A, *F, *Aalt, *Aalt);
	printf("%02x %02x %02x %02x\n", *B, *C, *Balt, *Calt);
	printf("%02x %02x %02x %02x\n", *D, *E, *Dalt, *Ealt);
	printf("%02x %02x %02x %02x\n", *H, *L, *Halt, *Lalt);
	printf("%02x %02x\n", *I, *R);
	printf("%02x %02x\n", *IX, *(IX + 1));
	printf("%02x %02x\n", *IY, *(IY + 1));
	printf("%02x %02x\n", *SP, *(SP + 1));
	printf("%02x %02x\n", *PC, *(PC + 1));
}

void default_ram_rw_testing(t_mem *mem)
{
	int i = 0;

	while (i < MEM_SIZE)
	{
		RAM[i] = i;
		i++;
	}
//	mem->rw[16] = 1;
//	mem->rw[17] = 255;
//	*PC += 2;
//	mem->rw[17] = 15;
//	mem->rw[14] = 10;
//	*PC += 10;
//	*(PC + 1) += 17;
//	*(PCA + 1) += 17;
//	&PC = 1;
}

int main(void)
{
	t_mem *mem;

	mem = (t_mem*)malloc(sizeof(t_mem));
	bzero(RW, RW_MEM_SIZE);
	bzero(RAM, MEM_SIZE);
	default_ram_rw_testing(mem);
	RW[17]++;
	print_reg_mem(mem);
	printf("\n");
	print_rw_mem(mem);
	printf("PC int = '%d'\n", PCV);
	printf("RAM AD int = '%d'\n", PCR);
	return (0);
}
