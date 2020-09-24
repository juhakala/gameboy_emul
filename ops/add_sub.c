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

// 0x09
int	add_hl_bc(t_mem *mem)
{
	if (PRINT)
		printing("ADD HL,", "BC", 1, mem);
	CLEAR_FLAG(6);
	if (((mem->reg->hl + mem->reg->bc) ^ mem->reg->hl ^ mem->reg->bc) & 0x1000)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((mem->reg->hl + mem->reg->bc) &0xffff0000)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->hl = mem->reg->hl + mem->reg->bc;
	mem->cycle += 8;
	return (1);
}

// 0x19
int	add_hl_de(t_mem *mem)
{
	if (PRINT)
		printing("ADD HL,", "DE", 1, mem);
	CLEAR_FLAG(6);
	if (((mem->reg->hl + mem->reg->de) ^ mem->reg->hl ^ mem->reg->de) & 0x1000)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((mem->reg->hl + mem->reg->de) &0xffff0000)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->hl = mem->reg->hl + mem->reg->de;
	mem->cycle += 8;
	return (1);
}

// 0x29
int	add_hl_hl(t_mem *mem)
{
	if (PRINT)
		printing("ADD HL,", "HL", 1, mem);
	CLEAR_FLAG(6);
	if (((mem->reg->hl + mem->reg->hl) ^ mem->reg->hl ^ mem->reg->hl) & 0x1000)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((mem->reg->hl + mem->reg->hl) &0xffff0000)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->hl = mem->reg->hl + mem->reg->hl;
	mem->cycle += 8;
	return (1);
}

// 0x39
int	add_hl_sp(t_mem *mem)
{
	if (PRINT)
		printing("ADD HL,", "SP", 1, mem);
	CLEAR_FLAG(6);
	if (((mem->reg->hl + mem->reg->sp) ^ mem->reg->hl ^ mem->reg->sp) & 0x1000)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((mem->reg->hl + mem->reg->sp) &0xffff0000)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->hl = mem->reg->hl + mem->reg->sp;
	mem->cycle += 8;
	return (1);
}

// 0x80
int	add_a_b(t_mem *mem)
{
	char a = mem->reg->a;
	char b = (mem->reg->bc >> 8) & 0xff;

	if (PRINT)
		printing("ADD A,", "B", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 4;
	return (1);
}

// 0x81
int	add_a_c(t_mem *mem)
{
	char a = mem->reg->a;
	char b = mem->reg->bc & 0xff;

	if (PRINT)
		printing("ADD A,", "C", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 4;
	return (1);
}

// 0x82
int	add_a_d(t_mem *mem)
{
	char a = mem->reg->a;
	char b = (mem->reg->de >> 8) & 0xff;

	if (PRINT)
		printing("ADD A,", "D", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 4;
	return (1);
}

// 0x83
int	add_a_e(t_mem *mem)
{
	char a = mem->reg->a;
	char b = mem->reg->de & 0xff;

	if (PRINT)
		printing("ADD A,", "E", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 4;
	return (1);
}

// 0x84
int	add_a_h(t_mem *mem)
{
	char a = mem->reg->a;
	char b = (mem->reg->hl >> 8) & 0xff;

	if (PRINT)
		printing("ADD A,", "H", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 4;
	return (1);
}

// 0x85
int	add_a_l(t_mem *mem)
{
	char a = mem->reg->a;
	char b = mem->reg->hl & 0xff;

	if (PRINT)
		printing("ADD A,", "L", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 4;
	return (1);
}

// 0x86
int	add_a_ahl(t_mem *mem)
{
	char a = mem->reg->a;
	char b = read(mem->reg->hl, mem);

	if (PRINT)
		printing("ADD A,", "(HL)", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 8;
	return (1);
}

// 0x87
int	add_a_a(t_mem *mem)
{
	char a = mem->reg->a;
	char b = mem->reg->a;

	if (PRINT)
		printing("ADD A,", "A", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 4;
	return (1);
}

// 0x90
int	sub_b(t_mem *mem)
{
	char a = mem->reg->a;
	char b = (mem->reg->bc >> 8) & 0xff;

	if (PRINT)
		printing("SUB B", "", 1, mem);
	if ((a - b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if (((a - b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a - b) & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a - b;
	mem->cycle += 4;
	return (1);
}

// 0x91
int	sub_c(t_mem *mem)
{
	char a = mem->reg->a;
	char b = mem->reg->bc & 0xff;

	if (PRINT)
		printing("SUB C", "", 1, mem);
	if ((a - b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if (((a - b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a - b) & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a - b;
	mem->cycle += 4;
	return (1);
}

// 0x92
int	sub_d(t_mem *mem)
{
	char a = mem->reg->a;
	char b = (mem->reg->de >> 8) & 0xff;

	if (PRINT)
		printing("SUB D", "", 1, mem);
	if ((a - b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if (((a - b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a - b) & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a - b;
	mem->cycle += 4;
	return (1);
}

// 0x93
int	sub_e(t_mem *mem)
{
	char a = mem->reg->a;
	char b = mem->reg->de & 0xff;

	if (PRINT)
		printing("SUB E", "", 1, mem);
	if ((a - b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if (((a - b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a - b) & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a - b;
	mem->cycle += 4;
	return (1);
}

// 0x94
int	sub_h(t_mem *mem)
{
	char a = mem->reg->a;
	char b = (mem->reg->hl >> 8) & 0xff;

	if (PRINT)
		printing("SUB H", "", 1, mem);
	if ((a - b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if (((a - b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a - b) & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a - b;
	mem->cycle += 4;
	return (1);
}

// 0x95
int	sub_l(t_mem *mem)
{
	char a = mem->reg->a;
	char b = mem->reg->hl & 0xff;

	if (PRINT)
		printing("SUB L", "", 1, mem);
	if ((a - b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if (((a - b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a - b) & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a - b;
	mem->cycle += 4;
	return (1);
}

// 0x90
int	sub_ahl(t_mem *mem)
{
	char a = mem->reg->a;
	char b = read(mem->reg->hl, mem);

	if (PRINT)
		printing("SUB (HL)", "", 1, mem);
	if ((a - b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if (((a - b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a - b) & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a - b;
	mem->cycle += 8;
	return (1);
}

// 0x91
int	sub_a(t_mem *mem)
{
	char a = mem->reg->a;
	char b = mem->reg->a;

	if (PRINT)
		printing("SUB A", "", 1, mem);
	if ((a - b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if (((a - b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a - b) & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a - b;
	mem->cycle += 4;
	return (1);
}

// 0x80
int	add_a_d8(t_mem *mem)
{
	char a = mem->reg->a;
	char b = read(mem->reg->pc + 1, mem);

	if (PRINT)
		printing("ADD A,", "B", 1, mem);
	if ((a + b) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if (((a + b) ^ a ^ b) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if ((unsigned short)(a + b) > 0x00ff)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->reg->a = a + b;
	mem->cycle += 8;
	return (2);
}
