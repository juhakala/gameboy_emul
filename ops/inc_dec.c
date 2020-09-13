#include "z80.h"
#include "struct.h"
#include "define.h"

static void printing(char *s1, char *s2, int size, t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, size);
	if (PRINT & 2)
		printf("	%s, %s", s1, s2);
	printf("\n");
}

// 0x03
int		inc_bc(t_mem *mem)
{
	if (PRINT)
		printing("INC", "BC", 1, mem);
	mem->reg->bc++;
	mem->cycle += 8;
	return (1);
}

// 0x05
int		dec_b(t_mem *mem)
{
	unsigned char val = (mem->reg->bc >> 8) & 0xff;

	if (PRINT)
		printing("DEC", "B", 1, mem);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (--val << 8);
	if (val == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if ((val & 0x0f) == 0x0f)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	mem->cycle += 4;
	return (1);
}

// 0x0c
int		inc_c(t_mem *mem)
{
	unsigned char val = mem->reg->bc & 0x00ff;

	if (PRINT)
		printing("INC", "C", 1, mem);
	mem->reg->bc = (mem->reg->bc & 0xff00) + ++val;
	if (val == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if ((val & 0x0f) == 0)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	mem->cycle += 4;
	return (1);
}

// 0x0d
int		dec_c(t_mem *mem)
{
	unsigned char val = mem->reg->bc & 0xff;

	if (PRINT)
		printing("DEC", "C", 1, mem);
	mem->reg->bc = (mem->reg->bc & 0xff) + --val;
	if (val == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if ((val & 0x0f) == 0x0f)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	mem->cycle += 4;
	return (1);
}

// 0x13
int		inc_de(t_mem *mem)
{
	if (PRINT)
		printing("INC", "DE", 1, mem);
	mem->reg->de++;
	mem->cycle += 8;
	return (1);
}

// 0x23
int		inc_hl(t_mem *mem)
{
	if (PRINT)
		printing("INC", "HL", 1, mem);
	mem->reg->hl++;
	mem->cycle += 8;
	return (1);
}

// 0x33
int		inc_sp(t_mem *mem)
{
	if (PRINT)
		printing("INC", "SP", 1, mem);
	mem->reg->sp++;
	mem->cycle += 8;
	return (1);
}

// 0x3d
int		dec_a(t_mem *mem)
{
	unsigned char val = (mem->reg->bc >> 8) & 0xff;

	if (PRINT)
		printing("DEC", "A", 1, mem);
	mem->reg->a--;
	if (mem->reg->a == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if ((mem->reg->a & 0x0f) == 0x0f)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	mem->cycle += 4;
	return (1);
}
