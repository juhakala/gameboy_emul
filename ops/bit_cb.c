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

static void	bit_x_x(int bit_n, unsigned char a, t_mem *mem)
{
	if (((a >> bit_n) & 1) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	SET_FLAG(5);
}

// 0x40
int		bit_0_b(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "0", "B", 2, mem);
	bit_x_x(0, mem->reg->bc >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x41
int		bit_0_c(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "0", "C", 2, mem);
	bit_x_x(0, mem->reg->bc & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x42
int		bit_0_d(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "0", "D", 2, mem);
	bit_x_x(0, mem->reg->de >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x43
int		bit_0_e(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "0", "E", 2, mem);
	bit_x_x(0, mem->reg->de & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x44
int		bit_0_h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "0", "H", 2, mem);
	bit_x_x(0, mem->reg->hl >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x45
int		bit_0_l(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "0", "L", 2, mem);
	bit_x_x(0, mem->reg->hl & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x46
int		bit_0_ahl(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "0", "(HL)", 2, mem);
	bit_x_x(0, read(mem->reg->hl, mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x47
int		bit_0_a(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "0", "A", 2, mem);
	bit_x_x(0, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x48
int		bit_1_b(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "1", "B", 2, mem);
	bit_x_x(1, mem->reg->bc >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x49
int		bit_1_c(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "1", "C", 2, mem);
	bit_x_x(1, mem->reg->bc & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x4a
int		bit_1_d(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "1", "D", 2, mem);
	bit_x_x(1, mem->reg->de >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x4b
int		bit_1_e(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "1", "E", 2, mem);
	bit_x_x(1, mem->reg->de & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x4c
int		bit_1_h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "1", "H", 2, mem);
	bit_x_x(1, mem->reg->hl >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x4d
int		bit_1_l(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "1", "L", 2, mem);
	bit_x_x(1, mem->reg->hl & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x4e
int		bit_1_ahl(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "1", "(HL)", 2, mem);
	bit_x_x(1, read(mem->reg->hl, mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x4f
int		bit_1_a(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "1", "A", 2, mem);
	bit_x_x(1, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x50
int		bit_2_b(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "2", "B", 2, mem);
	bit_x_x(2, mem->reg->bc >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x51
int		bit_2_c(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "2", "C", 2, mem);
	bit_x_x(2, mem->reg->bc & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x52
int		bit_2_d(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "2", "D", 2, mem);
	bit_x_x(2, mem->reg->de >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x53
int		bit_2_e(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "2", "E", 2, mem);
	bit_x_x(2, mem->reg->de & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x54
int		bit_2_h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "2", "H", 2, mem);
	bit_x_x(2, mem->reg->hl >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x55
int		bit_2_l(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "2", "L", 2, mem);
	bit_x_x(2, mem->reg->hl & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x56
int		bit_2_ahl(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "2", "(HL)", 2, mem);
	bit_x_x(2, read(mem->reg->hl, mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x57
int		bit_2_a(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "2", "A", 2, mem);
	bit_x_x(2, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x58
int		bit_3_b(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "3", "B", 2, mem);
	bit_x_x(3, mem->reg->bc >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x59
int		bit_3_c(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "3", "C", 2, mem);
	bit_x_x(3, mem->reg->bc & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x5a
int		bit_3_d(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "3", "D", 2, mem);
	bit_x_x(3, mem->reg->de >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x5b
int		bit_3_e(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "3", "E", 2, mem);
	bit_x_x(3, mem->reg->de & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x5c
int		bit_3_h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "3", "H", 2, mem);
	bit_x_x(3, mem->reg->hl >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x5d
int		bit_3_l(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "3", "L", 2, mem);
	bit_x_x(3, mem->reg->hl & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x5e
int		bit_3_ahl(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "3", "(HL)", 2, mem);
	bit_x_x(3, read(mem->reg->hl, mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x5f
int		bit_3_a(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "3", "A", 2, mem);
	bit_x_x(3, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x60
int		bit_4_b(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "4", "B", 2, mem);
	bit_x_x(4, mem->reg->bc >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x61
int		bit_4_c(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "4", "C", 2, mem);
	bit_x_x(4, mem->reg->bc & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x62
int		bit_4_d(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "4", "D", 2, mem);
	bit_x_x(4, mem->reg->de >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x63
int		bit_4_e(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "4", "E", 2, mem);
	bit_x_x(4, mem->reg->de & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x64
int		bit_4_h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "4", "H", 2, mem);
	bit_x_x(4, mem->reg->hl >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x65
int		bit_4_l(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "4", "L", 2, mem);
	bit_x_x(4, mem->reg->hl & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x66
int		bit_4_ahl(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "4", "(HL)", 2, mem);
	bit_x_x(4, read(mem->reg->hl, mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x67
int		bit_4_a(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "4", "A", 2, mem);
	bit_x_x(4, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x68
int		bit_5_b(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "5", "B", 2, mem);
	bit_x_x(5, mem->reg->bc >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x69
int		bit_5_c(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "5", "C", 2, mem);
	bit_x_x(5, mem->reg->bc & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x6a
int		bit_5_d(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "5", "D", 2, mem);
	bit_x_x(5, mem->reg->de >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x6b
int		bit_5_e(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "5", "E", 2, mem);
	bit_x_x(5, mem->reg->de & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x6c
int		bit_5_h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "5", "H", 2, mem);
	bit_x_x(5, mem->reg->hl >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x6d
int		bit_5_l(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "5", "L", 2, mem);
	bit_x_x(5, mem->reg->hl & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x6e
int		bit_5_ahl(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "5", "(HL)", 2, mem);
	bit_x_x(5, read(mem->reg->hl, mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x6f
int		bit_5_a(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "5", "A", 2, mem);
	bit_x_x(5, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x70
int		bit_6_b(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "6", "B", 2, mem);
	bit_x_x(6, mem->reg->bc >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x71
int		bit_6_c(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "6", "C", 2, mem);
	bit_x_x(6, mem->reg->bc & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x72
int		bit_6_d(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "6", "D", 2, mem);
	bit_x_x(6, mem->reg->de >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x73
int		bit_6_e(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "6", "E", 2, mem);
	bit_x_x(6, mem->reg->de & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x74
int		bit_6_h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "6", "H", 2, mem);
	bit_x_x(6, mem->reg->hl >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x75
int		bit_6_l(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "6", "L", 2, mem);
	bit_x_x(6, mem->reg->hl & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x76
int		bit_6_ahl(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "6", "(HL)", 2, mem);
	bit_x_x(6, read(mem->reg->hl, mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x77
int		bit_6_a(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "6", "A", 2, mem);
	bit_x_x(6, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}

// 0x78
int		bit_7_b(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "B", 2, mem);
	bit_x_x(7, mem->reg->bc >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x79
int		bit_7_c(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "C", 2, mem);
	bit_x_x(7, mem->reg->bc & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x7a
int		bit_7_d(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "D", 2, mem);
	bit_x_x(7, mem->reg->de >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x7b
int		bit_7_e(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "E", 2, mem);
	bit_x_x(7, mem->reg->de & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x7c
int		bit_7_h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "H", 2, mem);
	bit_x_x(7, mem->reg->hl >> 8, mem);
	mem->cycle += 8;
	return (2);
}

// 0x7d
int		bit_7_l(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "L", 2, mem);
	bit_x_x(7, mem->reg->hl & 0x00ff, mem);
	mem->cycle += 8;
	return (2);
}

// 0x7e
int		bit_7_ahl(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "(HL)", 2, mem);
	bit_x_x(7, read(mem->reg->hl, mem), mem);
	mem->cycle += 16;
	return (2);
}

// 0x7f
int		bit_7_a(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "A", 2, mem);
	bit_x_x(7, mem->reg->a, mem);
	mem->cycle += 8;
	return (2);
}
