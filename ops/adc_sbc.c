#include "z80.h"
#include "struct.h"
#include "define.h"

static void printing(char *s1, char *s2, char *s3, int size, t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, size);
	if (PRINT & 2)
		printf("	%s %s, %s", s1, s2, s3);
	printf("\n");
}

static void adc_a_x(unsigned char x, t_mem *mem)
{
	unsigned short n = mem->reg->a + x + CHECK_FLAG(4);
	if (n == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if ((n ^ mem->reg->a ^ x) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if (n & 0xff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = n & 0xff;
}

static void sdc_a_x(unsigned char x, t_mem *mem)
{
	unsigned short n = mem->reg->a - x - CHECK_FLAG(4);
	if (n == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if ((n ^ mem->reg->a ^ x) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if (n & 0xff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = n & 0xff;
}

// 0x88
int		adc_a_b(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "B", 1, mem);
	adc_a_x(mem->reg->bc >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0x89
int		adc_a_c(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "C", 1, mem);
	adc_a_x(mem->reg->bc & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0x8a
int		adc_a_d(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "D", 1, mem);
	adc_a_x(mem->reg->de >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0x8b
int		adc_a_e(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "E", 1, mem);
	adc_a_x(mem->reg->de & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0x8c
int		adc_a_h(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "H", 1, mem);
	adc_a_x(mem->reg->hl >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0x8d
int		adc_a_l(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "L", 1, mem);
	adc_a_x(mem->reg->hl & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0x8e
int		adc_a_ahl(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "B", 1, mem);
	adc_a_x(read(mem->reg->hl, mem), mem);
	mem->cycle += 8;
	return (1);
}

// 0x8f
int		adc_a_a(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "A", 1, mem);
	adc_a_x(mem->reg->a, mem);
	mem->cycle += 4;
	return (1);
}

// 0x98
int		sdc_a_b(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "B", 1, mem);
	sdc_a_x(mem->reg->bc >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0x99
int		sdc_a_c(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "C", 1, mem);
	sdc_a_x(mem->reg->bc & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0x9a
int		sdc_a_d(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "D", 1, mem);
	sdc_a_x(mem->reg->de >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0x9b
int		sdc_a_e(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "E", 1, mem);
	sdc_a_x(mem->reg->de & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0x9c
int		sdc_a_h(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "H", 1, mem);
	sdc_a_x(mem->reg->hl >> 8, mem);
	mem->cycle += 4;
	return (1);
}

// 0x9d
int		sdc_a_l(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "L", 1, mem);
	sdc_a_x(mem->reg->hl & 0x00ff, mem);
	mem->cycle += 4;
	return (1);
}

// 0x9e
int		sdc_a_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "B", 1, mem);
	sdc_a_x(read(mem->reg->hl, mem), mem);
	mem->cycle += 8;
	return (1);
}

// 0x9f
int		sdc_a_a(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "A", 1, mem);
	sdc_a_x(mem->reg->a, mem);
	mem->cycle += 4;
	return (1);
}

// 0xce
int		adc_a_d8(t_mem *mem)
{
	if (PRINT)
		printing("ADC", "A", "d8", 2, mem);
	adc_a_x(read(mem->reg->pc + 1, mem), mem);
	mem->cycle += 8;
	return (2);
}

// 0xde
int		sdc_a_d8(t_mem *mem)
{
	if (PRINT)
		printing("SDC", "A", "d8", 2, mem);
	sdc_a_x(read(mem->reg->pc + 1, mem), mem);
	mem->cycle += 8;
	return (2);
}
