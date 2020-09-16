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

static unsigned char bit_x_x(int bit_n, int set, unsigned char a, t_mem *mem)
{
	if (set == 1)
		a |= (1 << bit_n); // SET TO 1
	else if (set == 0)
		a &= ~(1 << bit_n); // CLEAR TO 0
	return (a);
}

// 0x80
int		res_0_b(t_mem *mem)
{
	if (PRINT)
		printing("RES", "0", "B", 2, mem);
	mem->reg->bc = (bit_x_x(0, 0, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x81
int		res_0_c(t_mem *mem)
{
	if (PRINT)
		printing("RES", "0", "C", 2, mem);
	mem->reg->bc = bit_x_x(0, 0, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x82
int		res_0_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "0", "D", 2, mem);
	mem->reg->de = (bit_x_x(0, 0, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x83
int		res_0_e(t_mem *mem)
{
	if (PRINT)
		printing("RES", "0", "E", 2, mem);
	mem->reg->de = bit_x_x(0, 0, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x84
int		res_0_h(t_mem *mem)
{
	if (PRINT)
		printing("RES", "0", "H", 2, mem);
	mem->reg->hl = (bit_x_x(0, 0, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x85
int		res_0_l(t_mem *mem)
{
	if (PRINT)
		printing("RES", "0", "L", 2, mem);
	mem->reg->hl = bit_x_x(0, 0, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x86
int		res_0_ahl(t_mem *mem)
{
	if (PRINT)
		printing("RES", "0", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(0, 0, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x87
int		res_0_a(t_mem *mem)
{
	if (PRINT)
		printing("RES", "0", "A", 2, mem);
	mem->reg->a = bit_x_x(0, 0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x88
int		res_1_b(t_mem *mem)
{
	if (PRINT)
		printing("RES", "1", "B", 2, mem);
	mem->reg->bc = (bit_x_x(1, 0, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x89
int		res_1_c(t_mem *mem)
{
	if (PRINT)
		printing("RES", "1", "C", 2, mem);
	mem->reg->bc = bit_x_x(1, 0, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x8a
int		res_1_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "1", "D", 2, mem);
	mem->reg->de = (bit_x_x(1, 0, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x8b
int		res_1_e(t_mem *mem)
{
	if (PRINT)
		printing("RES", "1", "E", 2, mem);
	mem->reg->de = bit_x_x(1, 0, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x8c
int		res_1_h(t_mem *mem)
{
	if (PRINT)
		printing("RES", "1", "H", 2, mem);
	mem->reg->hl = (bit_x_x(1, 0, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x8d
int		res_1_l(t_mem *mem)
{
	if (PRINT)
		printing("RES", "1", "L", 2, mem);
	mem->reg->hl = bit_x_x(1, 0, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x8e
int		res_1_ahl(t_mem *mem)
{
	if (PRINT)
		printing("RES", "1", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(1, 0, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x8f
int		res_1_a(t_mem *mem)
{
	if (PRINT)
		printing("RES", "1", "A", 2, mem);
	mem->reg->a = bit_x_x(1, 0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x90
int		res_2_b(t_mem *mem)
{
	if (PRINT)
		printing("RES", "2", "B", 2, mem);
	mem->reg->bc = (bit_x_x(2, 0, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x91
int		res_2_c(t_mem *mem)
{
	if (PRINT)
		printing("RES", "2", "C", 2, mem);
	mem->reg->bc = bit_x_x(2, 0, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x92
int		res_2_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "2", "D", 2, mem);
	mem->reg->de = (bit_x_x(2, 0, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x93
int		res_2_e(t_mem *mem)
{
	if (PRINT)
		printing("RES", "2", "E", 2, mem);
	mem->reg->de = bit_x_x(2, 0, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x94
int		res_2_h(t_mem *mem)
{
	if (PRINT)
		printing("RES", "2", "H", 2, mem);
	mem->reg->hl = (bit_x_x(2, 0, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x95
int		res_2_l(t_mem *mem)
{
	if (PRINT)
		printing("RES", "2", "L", 2, mem);
	mem->reg->hl = bit_x_x(2, 0, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x96
int		res_2_ahl(t_mem *mem)
{
	if (PRINT)
		printing("RES", "2", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(2, 0, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x97
int		res_2_a(t_mem *mem)
{
	if (PRINT)
		printing("RES", "2", "A", 2, mem);
	mem->reg->a = bit_x_x(2, 0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x98
int		res_3_b(t_mem *mem)
{
	if (PRINT)
		printing("RES", "3", "B", 2, mem);
	mem->reg->bc = (bit_x_x(3, 0, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x99
int		res_3_c(t_mem *mem)
{
	if (PRINT)
		printing("RES", "3", "C", 2, mem);
	mem->reg->bc = bit_x_x(3, 0, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x9a
int		res_3_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "3", "D", 2, mem);
	mem->reg->de = (bit_x_x(3, 0, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x9b
int		res_3_e(t_mem *mem)
{
	if (PRINT)
		printing("RES", "3", "E", 2, mem);
	mem->reg->de = bit_x_x(3, 0, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x9c
int		res_3_h(t_mem *mem)
{
	if (PRINT)
		printing("RES", "3", "H", 2, mem);
	mem->reg->hl = (bit_x_x(3, 0, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0x9d
int		res_3_l(t_mem *mem)
{
	if (PRINT)
		printing("RES", "3", "L", 2, mem);
	mem->reg->hl = bit_x_x(3, 0, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0x9e
int		res_3_ahl(t_mem *mem)
{
	if (PRINT)
		printing("RES", "3", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(3, 0, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x9f
int		res_3_a(t_mem *mem)
{
	if (PRINT)
		printing("RES", "3", "A", 2, mem);
	mem->reg->a = bit_x_x(3, 0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xa0
int		res_4_b(t_mem *mem)
{
	if (PRINT)
		printing("RES", "4", "B", 2, mem);
	mem->reg->bc = (bit_x_x(4, 0, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xa1
int		res_4_c(t_mem *mem)
{
	if (PRINT)
		printing("RES", "4", "C", 2, mem);
	mem->reg->bc = bit_x_x(4, 0, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xa2
int		res_4_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "4", "D", 2, mem);
	mem->reg->de = (bit_x_x(4, 0, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xa3
int		res_4_e(t_mem *mem)
{
	if (PRINT)
		printing("RES", "4", "E", 2, mem);
	mem->reg->de = bit_x_x(4, 0, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xa4
int		res_4_h(t_mem *mem)
{
	if (PRINT)
		printing("RES", "4", "H", 2, mem);
	mem->reg->hl = (bit_x_x(4, 0, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xa5
int		res_4_l(t_mem *mem)
{
	if (PRINT)
		printing("RES", "4", "L", 2, mem);
	mem->reg->hl = bit_x_x(4, 0, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xa6
int		res_4_ahl(t_mem *mem)
{
	if (PRINT)
		printing("RES", "4", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(4, 0, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xa7
int		res_4_a(t_mem *mem)
{
	if (PRINT)
		printing("RES", "4", "A", 2, mem);
	mem->reg->a = bit_x_x(4, 0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xa8
int		res_5_b(t_mem *mem)
{
	if (PRINT)
		printing("RES", "5", "B", 2, mem);
	mem->reg->bc = (bit_x_x(5, 0, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xa9
int		res_5_c(t_mem *mem)
{
	if (PRINT)
		printing("RES", "5", "C", 2, mem);
	mem->reg->bc = bit_x_x(5, 0, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xaa
int		res_5_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "5", "D", 2, mem);
	mem->reg->de = (bit_x_x(5, 0, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xab
int		res_5_e(t_mem *mem)
{
	if (PRINT)
		printing("RES", "5", "E", 2, mem);
	mem->reg->de = bit_x_x(5, 0, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xac
int		res_5_h(t_mem *mem)
{
	if (PRINT)
		printing("RES", "5", "H", 2, mem);
	mem->reg->hl = (bit_x_x(5, 0, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xad
int		res_5_l(t_mem *mem)
{
	if (PRINT)
		printing("RES", "5", "L", 2, mem);
	mem->reg->hl = bit_x_x(5, 0, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xae
int		res_5_ahl(t_mem *mem)
{
	if (PRINT)
		printing("RES", "5", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(5, 0, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xaf
int		res_5_a(t_mem *mem)
{
	if (PRINT)
		printing("RES", "5", "A", 2, mem);
	mem->reg->a = bit_x_x(5, 0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xb0
int		res_6_b(t_mem *mem)
{
	if (PRINT)
		printing("RES", "6", "B", 2, mem);
	mem->reg->bc = (bit_x_x(6, 0, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xb1
int		res_6_c(t_mem *mem)
{
	if (PRINT)
		printing("RES", "6", "C", 2, mem);
	mem->reg->bc = bit_x_x(6, 0, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xb2
int		res_6_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "6", "D", 2, mem);
	mem->reg->de = (bit_x_x(6, 0, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xb3
int		res_6_e(t_mem *mem)
{
	if (PRINT)
		printing("RES", "6", "E", 2, mem);
	mem->reg->de = bit_x_x(6, 0, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xb4
int		res_6_h(t_mem *mem)
{
	if (PRINT)
		printing("RES", "6", "H", 2, mem);
	mem->reg->hl = (bit_x_x(6, 0, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xb5
int		res_6_l(t_mem *mem)
{
	if (PRINT)
		printing("RES", "6", "L", 2, mem);
	mem->reg->hl = bit_x_x(6, 0, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xb6
int		res_6_ahl(t_mem *mem)
{
	if (PRINT)
		printing("RES", "6", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(6, 0, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xb7
int		res_6_a(t_mem *mem)
{
	if (PRINT)
		printing("RES", "6", "A", 2, mem);
	mem->reg->a = bit_x_x(6, 0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xb8
int		res_7_b(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "B", 2, mem);
	mem->reg->bc = (bit_x_x(7, 0, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xb9
int		res_7_c(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "C", 2, mem);
	mem->reg->bc = bit_x_x(7, 0, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xba
int		res_7_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "D", 2, mem);
	mem->reg->de = (bit_x_x(7, 0, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xbb
int		res_7_e(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "E", 2, mem);
	mem->reg->de = bit_x_x(7, 0, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xbc
int		res_7_h(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "H", 2, mem);
	mem->reg->hl = (bit_x_x(7, 0, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xbd
int		res_7_l(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "L", 2, mem);
	mem->reg->hl = bit_x_x(7, 0, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xbe
int		res_7_ahl(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(7, 0, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xbf
int		res_7_a(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "A", 2, mem);
	mem->reg->a = bit_x_x(7, 0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xc0
int		set_0_b(t_mem *mem)
{
	if (PRINT)
		printing("SET", "0", "B", 2, mem);
	mem->reg->bc = (bit_x_x(0, 1, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xc1
int		set_0_c(t_mem *mem)
{
	if (PRINT)
		printing("SET", "0", "C", 2, mem);
	mem->reg->bc = bit_x_x(0, 1, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xc2
int		set_0_d(t_mem *mem)
{
	if (PRINT)
		printing("SET", "0", "D", 2, mem);
	mem->reg->de = (bit_x_x(0, 1, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xc3
int		set_0_e(t_mem *mem)
{
	if (PRINT)
		printing("SET", "0", "E", 2, mem);
	mem->reg->de = bit_x_x(0, 1, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xc4
int		set_0_h(t_mem *mem)
{
	if (PRINT)
		printing("SET", "0", "H", 2, mem);
	mem->reg->hl = (bit_x_x(0, 1, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xc5
int		set_0_l(t_mem *mem)
{
	if (PRINT)
		printing("SET", "0", "L", 2, mem);
	mem->reg->hl = bit_x_x(0, 1, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xc6
int		set_0_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SET", "0", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(0, 1, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xc7
int		set_0_a(t_mem *mem)
{
	if (PRINT)
		printing("SET", "0", "A", 2, mem);
	mem->reg->a = bit_x_x(0, 1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xc8
int		set_1_b(t_mem *mem)
{
	if (PRINT)
		printing("SET", "1", "B", 2, mem);
	mem->reg->bc = (bit_x_x(1, 1, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xc9
int		set_1_c(t_mem *mem)
{
	if (PRINT)
		printing("SET", "1", "C", 2, mem);
	mem->reg->bc = bit_x_x(1, 1, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xca
int		set_1_d(t_mem *mem)
{
	if (PRINT)
		printing("SET", "1", "D", 2, mem);
	mem->reg->de = (bit_x_x(1, 1, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xcb
int		set_1_e(t_mem *mem)
{
	if (PRINT)
		printing("SET", "1", "E", 2, mem);
	mem->reg->de = bit_x_x(1, 1, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xcc
int		set_1_h(t_mem *mem)
{
	if (PRINT)
		printing("SET", "1", "H", 2, mem);
	mem->reg->hl = (bit_x_x(1, 1, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xcd
int		set_1_l(t_mem *mem)
{
	if (PRINT)
		printing("SET", "1", "L", 2, mem);
	mem->reg->hl = bit_x_x(1, 1, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xce
int		set_1_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SET", "1", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(1, 1, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xcf
int		set_1_a(t_mem *mem)
{
	if (PRINT)
		printing("SET", "1", "A", 2, mem);
	mem->reg->a = bit_x_x(1, 1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xd0
int		set_2_b(t_mem *mem)
{
	if (PRINT)
		printing("SET", "2", "B", 2, mem);
	mem->reg->bc = (bit_x_x(2, 1, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xd1
int		set_2_c(t_mem *mem)
{
	if (PRINT)
		printing("SET", "2", "C", 2, mem);
	mem->reg->bc = bit_x_x(2, 1, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xd2
int		set_2_d(t_mem *mem)
{
	if (PRINT)
		printing("SET", "2", "D", 2, mem);
	mem->reg->de = (bit_x_x(2, 1, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xd3
int		set_2_e(t_mem *mem)
{
	if (PRINT)
		printing("SET", "2", "E", 2, mem);
	mem->reg->de = bit_x_x(2, 1, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xd4
int		set_2_h(t_mem *mem)
{
	if (PRINT)
		printing("SET", "2", "H", 2, mem);
	mem->reg->hl = (bit_x_x(2, 1, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xd5
int		set_2_l(t_mem *mem)
{
	if (PRINT)
		printing("SET", "2", "L", 2, mem);
	mem->reg->hl = bit_x_x(2, 1, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xd6
int		set_2_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SET", "2", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(2, 1, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xd7
int		set_2_a(t_mem *mem)
{
	if (PRINT)
		printing("SET", "2", "A", 2, mem);
	mem->reg->a = bit_x_x(2, 1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xd8
int		set_3_b(t_mem *mem)
{
	if (PRINT)
		printing("SET", "3", "B", 2, mem);
	mem->reg->bc = (bit_x_x(3, 1, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xd9
int		set_3_c(t_mem *mem)
{
	if (PRINT)
		printing("SET", "3", "C", 2, mem);
	mem->reg->bc = bit_x_x(3, 1, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xda
int		set_3_d(t_mem *mem)
{
	if (PRINT)
		printing("SET", "3", "D", 2, mem);
	mem->reg->de = (bit_x_x(3, 1, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xdb
int		set_3_e(t_mem *mem)
{
	if (PRINT)
		printing("SET", "3", "E", 2, mem);
	mem->reg->de = bit_x_x(3, 1, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xdc
int		set_3_h(t_mem *mem)
{
	if (PRINT)
		printing("SET", "3", "H", 2, mem);
	mem->reg->hl = (bit_x_x(3, 1, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xdd
int		set_3_l(t_mem *mem)
{
	if (PRINT)
		printing("SET", "3", "L", 2, mem);
	mem->reg->hl = bit_x_x(3, 1, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xde
int		set_3_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SET", "3", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(3, 1, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xdf
int		set_3_a(t_mem *mem)
{
	if (PRINT)
		printing("SET", "3", "A", 2, mem);
	mem->reg->a = bit_x_x(3, 1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xe0
int		set_4_b(t_mem *mem)
{
	if (PRINT)
		printing("SET", "4", "B", 2, mem);
	mem->reg->bc = (bit_x_x(4, 1, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xe1
int		set_4_c(t_mem *mem)
{
	if (PRINT)
		printing("SET", "4", "C", 2, mem);
	mem->reg->bc = bit_x_x(4, 1, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xe2
int		set_4_d(t_mem *mem)
{
	if (PRINT)
		printing("SET", "4", "D", 2, mem);
	mem->reg->de = (bit_x_x(4, 1, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xe3
int		set_4_e(t_mem *mem)
{
	if (PRINT)
		printing("SET", "4", "E", 2, mem);
	mem->reg->de = bit_x_x(4, 1, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xe4
int		set_4_h(t_mem *mem)
{
	if (PRINT)
		printing("SET", "4", "H", 2, mem);
	mem->reg->hl = (bit_x_x(4, 1, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xe5
int		set_4_l(t_mem *mem)
{
	if (PRINT)
		printing("SET", "4", "L", 2, mem);
	mem->reg->hl = bit_x_x(4, 1, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xe6
int		set_4_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SET", "4", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(4, 1, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xe7
int		set_4_a(t_mem *mem)
{
	if (PRINT)
		printing("SET", "4", "A", 2, mem);
	mem->reg->a = bit_x_x(4, 1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xe8
int		set_5_b(t_mem *mem)
{
	if (PRINT)
		printing("SET", "5", "B", 2, mem);
	mem->reg->bc = (bit_x_x(5, 1, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xe9
int		set_5_c(t_mem *mem)
{
	if (PRINT)
		printing("SET", "5", "C", 2, mem);
	mem->reg->bc = bit_x_x(5, 1, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xea
int		set_5_d(t_mem *mem)
{
	if (PRINT)
		printing("SET", "5", "D", 2, mem);
	mem->reg->de = (bit_x_x(5, 1, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xeb
int		set_5_e(t_mem *mem)
{
	if (PRINT)
		printing("SET", "5", "E", 2, mem);
	mem->reg->de = bit_x_x(5, 1, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xec
int		set_5_h(t_mem *mem)
{
	if (PRINT)
		printing("SET", "5", "H", 2, mem);
	mem->reg->hl = (bit_x_x(5, 1, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xed
int		set_5_l(t_mem *mem)
{
	if (PRINT)
		printing("SET", "5", "L", 2, mem);
	mem->reg->hl = bit_x_x(5, 1, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xee
int		set_5_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SET", "5", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(5, 1, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xef
int		set_5_a(t_mem *mem)
{
	if (PRINT)
		printing("SET", "5", "A", 2, mem);
	mem->reg->a = bit_x_x(5, 1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xf0
int		set_6_b(t_mem *mem)
{
	if (PRINT)
		printing("SET", "6", "B", 2, mem);
	mem->reg->bc = (bit_x_x(6, 1, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xf1
int		set_6_c(t_mem *mem)
{
	if (PRINT)
		printing("SET", "6", "C", 2, mem);
	mem->reg->bc = bit_x_x(6, 1, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xf2
int		set_6_d(t_mem *mem)
{
	if (PRINT)
		printing("SET", "6", "D", 2, mem);
	mem->reg->de = (bit_x_x(6, 1, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xf3
int		set_6_e(t_mem *mem)
{
	if (PRINT)
		printing("SET", "6", "E", 2, mem);
	mem->reg->de = bit_x_x(6, 1, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xf4
int		set_6_h(t_mem *mem)
{
	if (PRINT)
		printing("SET", "6", "H", 2, mem);
	mem->reg->hl = (bit_x_x(6, 1, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xf5
int		set_6_l(t_mem *mem)
{
	if (PRINT)
		printing("SET", "6", "L", 2, mem);
	mem->reg->hl = bit_x_x(6, 1, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xf6
int		set_6_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SET", "6", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(6, 1, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xf7
int		set_6_a(t_mem *mem)
{
	if (PRINT)
		printing("SET", "6", "A", 2, mem);
	mem->reg->a = bit_x_x(6, 1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0xf8
int		set_7_b(t_mem *mem)
{
	if (PRINT)
		printing("SET", "7", "B", 2, mem);
	mem->reg->bc = (bit_x_x(7, 1, mem->reg->bc >> 8, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xf9
int		set_7_c(t_mem *mem)
{
	if (PRINT)
		printing("SET", "7", "C", 2, mem);
	mem->reg->bc = bit_x_x(7, 1, mem->reg->bc & 0x00ff, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xfa
int		set_7_d(t_mem *mem)
{
	if (PRINT)
		printing("RES", "7", "D", 2, mem);
	mem->reg->de = (bit_x_x(7, 1, mem->reg->de >> 8, mem) << 8) + (mem->reg->de & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xfb
int		set_7_e(t_mem *mem)
{
	if (PRINT)
		printing("SET", "7", "E", 2, mem);
	mem->reg->de = bit_x_x(7, 1, mem->reg->de & 0x00ff, mem) + (mem->reg->de & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xfc
int		set_7_h(t_mem *mem)
{
	if (PRINT)
		printing("SET", "7", "H", 2, mem);
	mem->reg->hl = (bit_x_x(7, 1, mem->reg->hl >> 8, mem) << 8) + (mem->reg->hl & 0x00ff);
	mem->cycle += 8;
	return (2);
}

// 0xfd
int		set_7_l(t_mem *mem)
{
	if (PRINT)
		printing("SET", "7", "L", 2, mem);
	mem->reg->hl = bit_x_x(7, 1, mem->reg->hl & 0x00ff, mem) + (mem->reg->hl & 0xff00);
	mem->cycle += 8;
	return (2);
}

// 0xfe
int		set_7_ahl(t_mem *mem)
{
	if (PRINT)
		printing("SET", "7", "(HL)", 2, mem);
	write(mem->reg->hl, bit_x_x(7, 1, read(mem->reg->hl, mem), mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0xff
int		set_7_a(t_mem *mem)
{
	if (PRINT)
		printing("SET", "7", "A", 2, mem);
	mem->reg->a = bit_x_x(7, 1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}
