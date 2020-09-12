#include "z80.h"
#include "define.h"

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
