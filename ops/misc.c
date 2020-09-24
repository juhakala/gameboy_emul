#include "z80.h"
#include "struct.h"
#include "define.h"

static void printing(char *s1, char *s2, int size, t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, size);
	if (PRINT & 2)
		printf("	%s %s", s1, s2);
	printf("\n");
}

// 0x07
int		rlca(t_mem *mem)
{
	int carry;

	if (PRINT)
		printing("RLCA", "", 1, mem);
	mem->reg->a = (mem->reg->a << 1) + (mem->reg->a >> 7);
	CLEAR_FLAG(7);
    CLEAR_FLAG(6);
    CLEAR_FLAG(5);
	if ((mem->reg->a >> 7) == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->cycle += 4;
	return (1);
}

// 0x07
int		stop(t_mem *mem)
{
	if (PRINT)
		printing("STOP", "", 2, mem);
	mem->halt = 1;
	mem->io_reg->ffff = 0;
	mem->cycle += 4;
	return (2);
}

// 0x11
int		rla(t_mem *mem)
{
	int carry;

	if (PRINT)
		printing("RLA", "", 1, mem);
    carry = (mem->reg->a >> 7) & 1;
    mem->reg->a = (mem->reg->a << 1) + CHECK_FLAG(4);
	CLEAR_FLAG(7);
    CLEAR_FLAG(6);
    CLEAR_FLAG(5);
    if (carry == 1)
        SET_FLAG(4);
    else
        CLEAR_FLAG(4);
    mem->cycle += 4;
    return (1);
}

/*
// 0x27
int		daa(t_mem *mem)
{
	int carry;

	if (PRINT)
		printing("DAA", "", 1, mem);
	
	mem->cycle += 4;
	return (1);
}
*/

// 0x37
int		scf(t_mem *mem)
{
	int carry;

	if (PRINT)
		printing("SCF", "", 1, mem);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	SET_FLAG(4);
	mem->cycle += 4;
	return (1);
}

// 0x76
int		halt(t_mem *mem)
{
	if (PRINT)
		printing("HALT", "", 2, mem);
	mem->halt = 1;
	mem->cycle += 4;
	return (2);
}

// 0xc7
int		rst_00(t_mem *mem)
{
	if (PRINT)
		printing("RST", "00H", 2, mem);
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x00;
	mem->cycle += 32;
	return (0);
}

// 0xcf
int		rst_08(t_mem *mem)
{
	if (PRINT)
		printing("RST", "08H", 2, mem);
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x08;
	mem->cycle += 32;
	return (0);
}

// 0xd7
int		rst_10(t_mem *mem)
{
	if (PRINT)
		printing("RST", "10H", 2, mem);
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x10;
	mem->cycle += 32;
	return (0);
}

// 0xdf
int		rst_18(t_mem *mem)
{
	if (PRINT)
		printing("RST", "18H", 2, mem);
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x18;
	mem->cycle += 32;
	return (0);
}

// 0xe7
int		rst_20(t_mem *mem)
{
	if (PRINT)
		printing("RST", "20H", 2, mem);
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x20;
	mem->cycle += 32;
	return (0);
}

// 0xef
int		rst_28(t_mem *mem)
{
	if (PRINT)
		printing("RST", "28H", 2, mem);
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x28;
	mem->cycle += 32;
	return (0);
}

// 0xf3
int		di(t_mem *mem)
{
	if (PRINT)
		printing("DI", "", 1, mem);
	mem->master_interrupt = 0;
	mem->cycle += 4;
	return (1);
}

// 0xf7
int		rst_30(t_mem *mem)
{
	if (PRINT)
		printing("RST", "30H", 2, mem);
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x30;
	mem->cycle += 32;
	return (0);
}

// 0xff
int		rst_38(t_mem *mem)
{
	if (PRINT)
		printing("RST", "38H", 2, mem);
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x38;
	mem->cycle += 32;
	return (0);
}
