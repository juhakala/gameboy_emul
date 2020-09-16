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

static void	cp_x(unsigned char x, t_mem *mem)
{
	unsigned short val = mem->reg->a - x;
	if (val == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if ((mem->reg->a ^ x ^ val) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if (val & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
}

static void	or_x(unsigned char x, t_mem *mem)
{
	mem->reg->a = mem->reg->a | x;
	if (mem->reg->a == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
}

// 0xb0
int     or_b(t_mem *mem)
{
	if (PRINT)
		printing("OR", "B", 1, mem);
	or_x(mem->reg->bc >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0xb1
int     or_c(t_mem *mem)
{
	if (PRINT)
		printing("OR", "C", 1, mem);
	or_x(mem->reg->bc & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0xb2
int     or_d(t_mem *mem)
{
	if (PRINT)
		printing("OR", "D", 1, mem);
	or_x(mem->reg->de >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0xb3
int     or_e(t_mem *mem)
{
	if (PRINT)
		printing("OR", "E", 1, mem);
	or_x(mem->reg->de & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0xb4
int     or_h(t_mem *mem)
{
	if (PRINT)
		printing("OR", "H", 1, mem);
	or_x(mem->reg->hl >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0xb5
int     or_l(t_mem *mem)
{
	if (PRINT)
		printing("OR", "L", 1, mem);
	or_x(mem->reg->hl & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0xb6
int     or_ahl(t_mem *mem)
{
	if (PRINT)
		printing("OR", "(HL)", 1, mem);
	or_x(read(mem->reg->hl, mem), mem);
	mem->cycle += 8;
	return (1);
}

// 0xb7
int     or_a(t_mem *mem)
{
	if (PRINT)
		printing("OR", "A", 1, mem);
	or_x(mem->reg->a, mem);
	mem->cycle += 4;
	return (1);
}

// 0xb8
int     cp_b(t_mem *mem)
{
	if (PRINT)
		printing("CP", "B", 1, mem);
	cp_x(mem->reg->bc >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0xb9
int     cp_c(t_mem *mem)
{
	if (PRINT)
		printing("CP", "C", 1, mem);
	cp_x(mem->reg->bc & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0xba
int     cp_d(t_mem *mem)
{
	if (PRINT)
		printing("CP", "D", 1, mem);
	cp_x(mem->reg->de >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0xbb
int     cp_e(t_mem *mem)
{
	if (PRINT)
		printing("CP", "E", 1, mem);
	cp_x(mem->reg->de & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0xbc
int     cp_h(t_mem *mem)
{
	if (PRINT)
		printing("CP", "H", 1, mem);
	cp_x(mem->reg->hl >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0xbd
int     cp_l(t_mem *mem)
{
	if (PRINT)
		printing("CP", "L", 1, mem);
	cp_x(mem->reg->hl & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0xbe
int     cp_ahl(t_mem *mem)
{
	if (PRINT)
		printing("CP", "(HL)", 1, mem);
	cp_x(read(mem->reg->hl, mem), mem);
	mem->cycle += 8;
	return (1);
}

// 0xbf
int     cp_a(t_mem *mem)
{
	if (PRINT)
		printing("CP", "A", 1, mem);
	cp_x(mem->reg->a, mem);
	mem->cycle += 4;
	return (1);
}

// 0xf6
int     or_d8(t_mem *mem)
{
	if (PRINT)
		printing("OR", "d8", 2, mem);
	or_x(read(mem->reg->pc + 1, mem), mem);
	mem->cycle += 8;
	return (2);
}

// 0xfe
int     cp_d8(t_mem *mem)
{
	if (PRINT)
		printing("CP", "d8", 2, mem);
	cp_x(read(mem->reg->pc + 1, mem), mem);
	mem->cycle += 8;
	return (2);
}
