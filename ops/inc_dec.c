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

// 0x04
int		inc_b(t_mem *mem)
{
	unsigned char val;
	if (PRINT)
		printing("INC", "B", 1, mem);
	val = ((mem->reg->bc & 0xff00) >> 8) + 1;
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (val << 8);
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

// 0x05
int		dec_b(t_mem *mem)
{
	unsigned char val = (mem->reg->bc >> 8) & 0xff;

	if (PRINT)
		printing("DEC", "B", 1, mem);
//	printf("%04x\n", mem->reg->bc);
//	printf("%02x\n", (mem->reg->bc >> 8) & 0xff);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (--val << 8);
//	printf("%02x\n", (mem->reg->bc >> 8) & 0xff);
//	printf("%04x\n", mem->reg->hl);
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

// 0x0b
int		dec_bc(t_mem *mem)
{
	if (PRINT)
		printing("DEC", "BC", 1, mem);
	mem->reg->bc--;
	mem->cycle += 8;
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
	mem->reg->bc = (mem->reg->bc & 0xff00) + --val;
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

// 0x14
int		inc_d(t_mem *mem)
{
	unsigned char val;
	if (PRINT)
		printing("INC", "D", 1, mem);
	val = ((mem->reg->de & 0xff00) >> 8) + 1;
	mem->reg->de = (mem->reg->de & 0x00ff) + (val << 8);
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

// 0x15
int		dec_d(t_mem *mem)
{
	unsigned char val = (mem->reg->de >> 8) & 0xff;

	if (PRINT)
		printing("DEC", "D", 1, mem);
	mem->reg->de = (mem->reg->de & 0x00ff) + (--val << 8);
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

// 0x1b
int		dec_de(t_mem *mem)
{
	if (PRINT)
		printing("DEC", "DE", 1, mem);
	mem->reg->de--;
	mem->cycle += 8;
	return (1);
}

// 0x1c
int		inc_e(t_mem *mem)
{
	unsigned char val = mem->reg->de & 0x00ff;

	if (PRINT)
		printing("INC", "E", 1, mem);
	mem->reg->de = (mem->reg->de & 0xff00) + ++val;
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

// 0x1d
int		dec_e(t_mem *mem)
{
	unsigned char val = mem->reg->de & 0xff;

	if (PRINT)
		printing("DEC", "E", 1, mem);
	mem->reg->de = (mem->reg->de & 0xff00) + --val;
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

// 0x23
int		inc_hl(t_mem *mem)
{
	if (PRINT)
		printing("INC", "HL", 1, mem);
	mem->reg->hl++;
	mem->cycle += 8;
	return (1);
}

// 0x24
int		inc_h(t_mem *mem)
{
	unsigned char val;
	if (PRINT)
		printing("INC", "H", 1, mem);
	val = ((mem->reg->hl & 0xff00) >> 8) + 1;
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (val << 8);
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

// 0x25
int		dec_h(t_mem *mem)
{
	unsigned char val = (mem->reg->hl >> 8) & 0xff;

	if (PRINT)
		printing("DEC", "H", 1, mem);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (--val << 8);
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

// 0x2b
int		dec_hl(t_mem *mem)
{
	if (PRINT)
		printing("DEC", "HL", 1, mem);
	mem->reg->hl--;
	mem->cycle += 8;
	return (1);
}

// 0x2c
int		inc_l(t_mem *mem)
{
	unsigned char val = mem->reg->hl & 0x00ff;

	if (PRINT)
		printing("INC", "L", 1, mem);
	mem->reg->hl = (mem->reg->hl & 0xff00) + ++val;
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

// 0x2d
int		dec_l(t_mem *mem)
{
	unsigned char val = mem->reg->hl & 0xff;

	if (PRINT)
		printing("DEC", "L", 1, mem);
	mem->reg->hl = (mem->reg->hl & 0xff00) + --val;
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

// 0x33
int		inc_sp(t_mem *mem)
{
	if (PRINT)
		printing("INC", "SP", 1, mem);
	mem->reg->sp++;
	mem->cycle += 8;
	return (1);
}

// 0x34
int		inc_ahl(t_mem *mem)
{
	unsigned short val = read(mem->reg->hl, mem) + 1;
	if (PRINT)
		printing("INC", "(HL)", 1, mem);
	write(mem->reg->hl, val & 0x00ff, mem);
	if (val == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if ((val & 0x0f) == 0x00)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	mem->cycle += 12;
	return (1);
}

// 0x35
int		dec_ahl(t_mem *mem)
{
	unsigned short val = read(mem->reg->hl, mem) - 1;
	if (PRINT)
		printing("DEC", "(HL)", 1, mem);
	write(mem->reg->hl, val, mem);
	if (val == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if ((val & 0x0f) == 0x00)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	mem->cycle += 12;
	return (1);
}

// 0x3b
int		dec_sp(t_mem *mem)
{
	if (PRINT)
		printing("DEC", "SP", 1, mem);
	mem->reg->sp--;
	mem->cycle += 8;
	return (1);
}

// 0x3c
int		inc_a(t_mem *mem)
{
	if (PRINT)
		printing("INC", "A", 1, mem);
	mem->reg->a++;
	unsigned char val = mem->reg->a;
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

// 0x3d
int		dec_a(t_mem *mem)
{
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
