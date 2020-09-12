#include "z80.h"
#include "struct.h"
#include "define.h"

static void	printing(char *s1, char *s2, int size, t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, size);
	if (PRINT & 2)
		printf("	LD %s, %s", s1, s2);
	printf("\n");
}

// 0x0e
int	ld_c_d8(t_mem *mem)
{
	if (PRINT)
		printing("C", "s8", 2, mem);
	mem->reg->bc = (mem->reg->bc & 0xff00) + read(mem->reg->pc + 1, mem);
	mem->cycle += 8;
	return (2);
}

// 0x21
int	ld_hl_d16(t_mem *mem)
{
	if (PRINT)
		printing("HL", "d16", 3, mem);
	mem->reg->hl = read(mem->reg->pc + 1, mem);
	mem->reg->hl += read(mem->reg->pc + 2, mem) << 8;
	mem->cycle += 12;
	return (3);
}

// 0x31
int	ld_sp_d16(t_mem *mem)
{
	if (PRINT)
		printing("SP", "d16", 3, mem);
	mem->reg->sp = read(mem->reg->pc + 1, mem);
	mem->reg->sp += read(mem->reg->pc + 2, mem) << 8;
	mem->cycle += 12;
	return (3);
}

// 0x32
int	ld_ahln_a(t_mem *mem)
{
	if (PRINT)
		printing("(HL-)", "A", 1, mem);
	write(mem->reg->hl--, mem->reg->a, mem);
	mem->cycle += 8;
	return (1);
}

// 0x3e
int	ld_a_d8(t_mem *mem)
{
	if (PRINT)
		printing("A", "d8", 2, mem);
	mem->reg->a = read(mem->reg->pc + 1, mem);
	mem->cycle += 8;
	return (2);
}

// 0x77
int	ld_ahl_a(t_mem *mem)
{
	if (PRINT)
		printing("(HL)", "A", 1, mem);
	write(mem->reg->hl, mem->reg->a, mem);
	mem->cycle += 8;
	return (1);
}

// 0xe0
int	ld_ad8_a(t_mem *mem)
{
	unsigned char val = read(mem->reg->pc + 1, mem);;
	if (PRINT)
		printing("($FF00 + d8)", "A", 2, mem);
	if (val >= 0x0000 && val <= 0x007f)
		mem->i_o_registers[val] = mem->reg->a;
	else if (val >= 0x0080 && val <= 0x00fe)
		mem->hram[val - 0x80] = mem->reg->a;
	else if (val == 0x00ff)
		mem->interrupts = mem->reg->a;
	mem->cycle += 8;
	return (2);
}

// 0xe2
int	ld_ac_a(t_mem *mem)
{
	unsigned char val = (unsigned char)(mem->reg->bc & 0xff);
	if (PRINT)
		printing("($FF00 + C)", "A", 1, mem);
	if (val >= 0x0000 && val <= 0x007f)
		mem->i_o_registers[val] = mem->reg->a;
	else if (val >= 0x0080 && val <= 0x00fe)
		mem->hram[val - 0x80] = mem->reg->a;
	else if (val == 0x00ff)
		mem->interrupts = mem->reg->a;
	mem->cycle += 8;
	return (1);
}
