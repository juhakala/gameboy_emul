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

// 0x01
int	ld_bc_d16(t_mem *mem)
{
	if (PRINT)
		printing("BC", "d16", 3, mem);
	mem->reg->bc = read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8);
	mem->cycle += 12;
	return (3);
}

// 0x02
int	ld_abc_a(t_mem *mem)
{
	if (PRINT)
		printing("(BC)", "A", 1, mem);
	write(mem->reg->bc, mem->reg->a, mem);
	mem->cycle += 8;
	return (1);
}

// 0x06
int	ld_b_d8(t_mem *mem)
{
	if (PRINT)
		printing("B", "d8", 2, mem);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (read(mem->reg->pc + 1, mem) << 8);
	mem->cycle += 8;
	return (2);
}

// 0x08
int	ld_a16_sp(t_mem *mem)
{
	unsigned short addr;
	if (PRINT)
		printing("(a16)", "SP", 3, mem);
	addr = read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8);
	write(addr, mem->reg->sp & 0x00ff, mem);
	write(addr + 1, (mem->reg->sp >> 8) & 0x00ff, mem);
	mem->cycle += 20;
	return (3);
}

// 0x0a
int	ld_a_abc(t_mem *mem)
{
	if (PRINT)
		printing("A", "(BC)", 1, mem);
	mem->reg->a = read(mem->reg->bc, mem);
	mem->cycle += 8;
	return (1);
}

// 0x0e
int	ld_c_d8(t_mem *mem)
{
	if (PRINT)
		printing("C", "d8", 2, mem);
	mem->reg->bc = (mem->reg->bc & 0xff00) + read(mem->reg->pc + 1, mem);
	mem->cycle += 8;
	return (2);
}

// 0x11
int	ld_de_d16(t_mem *mem)
{
	if (PRINT)
		printing("DE", "d16", 3, mem);
	mem->reg->de = read(mem->reg->pc + 1, mem);
	mem->reg->de += read(mem->reg->pc + 2, mem) << 8;
	mem->cycle += 12;
	return (3);
}

// 0x12
int	ld_ade_a(t_mem *mem)
{
	if (PRINT)
		printing("(DE)", "A", 1, mem);
	write(mem->reg->de, mem->reg->a, mem);
	mem->cycle += 8;
	return (1);
}

// 0x16
int	ld_d_d8(t_mem *mem)
{
	if (PRINT)
		printing("D", "d8", 2, mem);
	mem->reg->de = (mem->reg->de & 0x00ff) + (read(mem->reg->pc + 1, mem) << 8);
	mem->cycle += 8;
	return (2);
}

// 0x1a
int	ld_a_ade(t_mem *mem)
{
	if (PRINT)
		printing("A", "(DE)", 1, mem);
	mem->reg->a = read(mem->reg->de, mem);
	mem->cycle += 8;
	return (1);
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

// 0x22
int	ld_ahlp_a(t_mem *mem)
{
	if (PRINT)
		printing("(HL+)", "A", 1, mem);
	write(mem->reg->hl++, mem->reg->a, mem);
	mem->cycle += 8;
	return (1);
}

// 0x26
int	ld_h_d8(t_mem *mem)
{
	if (PRINT)
		printing("H", "d8", 2, mem);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (read(mem->reg->pc + 1, mem) << 8);
	mem->cycle += 8;
	return (2);
}

// 0x2e
int	ld_l_d8(t_mem *mem)
{
	if (PRINT)
		printing("L", "d8", 2, mem);
	mem->reg->hl = (mem->reg->hl & 0xff00) + read(mem->reg->pc + 1, mem);
	mem->cycle += 8;
	return (2);
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

// 0x40
int	ld_b_b(t_mem *mem)
{
	if (PRINT)
		printing("B", "B", 1, mem);
	mem->reg->bc = (mem->reg->bc & 0xff00) + (mem->reg->bc & 0x00ff);
	mem->cycle += 4;
	return (1);
}

// 0x41
int	ld_b_c(t_mem *mem)
{
	if (PRINT)
		printing("B", "C", 1, mem);
	mem->reg->bc = ((mem->reg->bc & 0x00ff) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 4;
	return (1);
}

// 0x42
int	ld_b_d(t_mem *mem)
{
	if (PRINT)
		printing("B", "D", 1, mem);
	mem->reg->bc = (mem->reg->de & 0xff00) + (mem->reg->bc & 0x00ff);
	mem->cycle += 4;
	return (1);
}

// 0x43
int	ld_b_e(t_mem *mem)
{
	if (PRINT)
		printing("B", "E", 1, mem);
	mem->reg->bc = ((mem->reg->de & 0x00ff) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 4;
	return (1);
}

// 0x44
int	ld_b_h(t_mem *mem)
{
	if (PRINT)
		printing("B", "H", 1, mem);
	mem->reg->bc = (mem->reg->hl & 0xff00) + (mem->reg->bc & 0x00ff);
	mem->cycle += 4;
	return (1);
}

// 0x45
int	ld_b_l(t_mem *mem)
{
	if (PRINT)
		printing("B", "L", 1, mem);
	mem->reg->bc = ((mem->reg->hl & 0x00ff) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 4;
	return (1);
}

// 0x46
int	ld_b_ahl(t_mem *mem)
{
	if (PRINT)
		printing("B", "(HL)", 1, mem);
	mem->reg->bc = (read(mem->reg->hl, mem) << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 8;
	return (1);
}

// 0x47
int	ld_b_a(t_mem *mem)
{
	if (PRINT)
		printing("B", "A", 1, mem);
	mem->reg->bc = (mem->reg->a << 8) + (mem->reg->bc & 0x00ff);
	mem->cycle += 4;
	return (1);
}
////

// 0x48
int	ld_c_b(t_mem *mem)
{
	if (PRINT)
		printing("C", "B", 1, mem);
	mem->reg->bc = (mem->reg->bc & 0xff00) + ((mem->reg->bc & 0xff00) >> 8);
	mem->cycle += 4;
	return (1);
}

// 0x49
int	ld_c_c(t_mem *mem)
{
	if (PRINT)
		printing("C", "C", 1, mem);
	mem->reg->bc = (mem->reg->bc & 0xff00) + (mem->reg->bc & 0x00ff);
	mem->cycle += 4;
	return (1);
}

// 0x4a
int	ld_c_d(t_mem *mem)
{
	if (PRINT)
		printing("C", "D", 1, mem);
	mem->reg->bc = ((mem->reg->de & 0xff00) >> 8) + (mem->reg->bc & 0xff00);
	mem->cycle += 4;
	return (1);
}

// 0x4b
int	ld_c_e(t_mem *mem)
{
	if (PRINT)
		printing("C", "E", 1, mem);
	mem->reg->bc = (mem->reg->de & 0x00ff) + (mem->reg->bc & 0xff00);
	mem->cycle += 4;
	return (1);
}

// 0x4c
int	ld_c_h(t_mem *mem)
{
	if (PRINT)
		printing("C", "H", 1, mem);
	mem->reg->bc = ((mem->reg->hl & 0xff00) >> 8) + (mem->reg->bc & 0xff00);
	mem->cycle += 4;
	return (1);
}

// 0x4d
int	ld_c_l(t_mem *mem)
{
	if (PRINT)
		printing("C", "L", 1, mem);
	mem->reg->bc = (mem->reg->hl & 0x00ff) + (mem->reg->bc & 0xff00);
	mem->cycle += 4;
	return (1);
}

// 0x4e
int	ld_c_ahl(t_mem *mem)
{
	if (PRINT)
		printing("C", "(HL)", 1, mem);
	mem->reg->bc = read(mem->reg->hl, mem) + (mem->reg->bc & 0xff00);
	mem->cycle += 8;
	return (1);
}

// 0x4f
int	ld_c_a(t_mem *mem)
{
	if (PRINT)
		printing("C", "A", 1, mem);
	mem->reg->bc = mem->reg->a + (mem->reg->bc & 0xff00);
	mem->cycle += 4;
	return (1);
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

// 0x7b
int	ld_a_e(t_mem *mem)
{
	if (PRINT)
		printing("A", "E", 1, mem);
	mem->reg->a = mem->reg->de & 0x00ff;
	mem->cycle += 4;
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

// 0xea
int	ld_ad16_a(t_mem *mem)
{
	unsigned short addr;

	if (PRINT)
		printing("(d16)", "A", 3, mem);
	addr = (read(mem->reg->pc + 2, mem) << 8) + read(mem->reg->pc + 1, mem);
	write(addr, mem->reg->a, mem);
	mem->cycle += 16;
	return (3);
}

// 0xf0
int	ld_a_ad8(t_mem *mem)
{
	if (PRINT)
		printing("A", "($FF)) + d8", 2, mem);
	mem->reg->a = read(read(mem->reg->pc + 1, mem) + 0xff00, mem);
	mem->cycle += 12;
	return (2);
}

// 0xf0
int	ld_a_ac(t_mem *mem)
{
	if (PRINT)
		printing("A", "($FF)) + d8", 2, mem);
	mem->reg->a = read((mem->reg->bc & 0x00ff) + 0xff00, mem);
	mem->cycle += 12;
	return (2);
}
