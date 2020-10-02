#include "z80.h"
#include "struct.h"
#include "define.h"
#include "op.h"

// 0x00
int op_nop(t_mem *mem)
{
	return (1);
}

// 0x01
int ld_bc_d16(t_mem *mem)
{
	mem->reg->bc = read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8);
	return (3);
}

// 0x02
int ld_abc_a(t_mem *mem)
{
	write(mem->reg->bc, mem->reg->a, mem);
	return (1);
}

// 0x03
int inc_bc(t_mem *mem)
{
	mem->reg->bc += 1;
	return (1);
}

// 0x04
int inc_b(t_mem *mem)
{
	opcodes_inc((unsigned char*)&mem->reg->bc + 1, mem);
	return (1);
}

// 0x05
int dec_b(t_mem *mem)
{
	opcodes_dec((unsigned char*)&mem->reg->bc + 1, mem);
	return (1);
}

// 0x06
int ld_b_d8(t_mem *mem)
{
	*((unsigned char*)&mem->reg->bc + 1) = read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x07
int rlca(t_mem *mem)
{
	opcodes_rlc(&mem->reg->a, mem);
	return (1);
}

// 0x08
int ld_a16_sp(t_mem *mem)
{	
	unsigned short addr = read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8);
	write(addr, mem->reg->sp & 0xff, mem);
	write(addr + 1, (mem->reg->sp >> 8) & 0xff, mem);
	return (3);
}

// 0x09
int add_hl_bc(t_mem *mem)
{
	opcodes_add_hl(mem->reg->bc, mem);
	return (1);
}

// 0x0a
int ld_a_abc(t_mem *mem)
{
	mem->reg->a = read(mem->reg->bc, mem);
	return (1);
}

// 0x0b
int dec_bc(t_mem *mem)
{
	mem->reg->bc--;
	return (1);
}

// 0x0c
int inc_c(t_mem *mem)
{
	opcodes_inc((unsigned char*)&mem->reg->bc, mem);
	return (1);
}

// 0x0d
int dec_c(t_mem *mem)
{
	opcodes_dec((unsigned char*)&mem->reg->bc, mem);
	return (1);
}

// 0x0e
int ld_c_d8(t_mem *mem)
{
	mem->reg->bc = (mem->reg->bc & 0xff00) + read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x0f
int rrca(t_mem *mem)
{
	opcodes_rrc(&mem->reg->a, mem);
	return (1);
}

// 0x10
int stop(t_mem *mem)
{
	mem->halt = 1;
	*mem->io_reg->ffff = 0;
	return (2);
}

// 0x11
int ld_de_d16(t_mem *mem)
{
	mem->reg->de = read(mem->reg->pc + 1, mem);
	mem->reg->de += read(mem->reg->pc + 2, mem) << 8;
	return (3);
}

// 0x12
int ld_ade_a(t_mem *mem)
{
	write(mem->reg->de, mem->reg->a, mem);
	return (1);
}

// 0x13
int inc_de(t_mem *mem)
{
	mem->reg->de++;
	return (1);
}

// 0x14
int inc_d(t_mem *mem)
{
	opcodes_inc((unsigned char*)&mem->reg->de + 1, mem);
	return (1);
}

// 0x15
int dec_d(t_mem *mem)
{
	opcodes_dec((unsigned char*)&mem->reg->de + 1, mem);
	return (1);
}

// 0x16
int ld_d_d8(t_mem *mem)
{
	mem->reg->de = (mem->reg->de & 0x00ff) + (read(mem->reg->pc + 1, mem) << 8);
	return (2);
}

// 0x17
int rla(t_mem *mem)
{
	opcodes_rl(&mem->reg->a, mem);
	return (1);
}

// 0x18
int jr_s8(t_mem *mem)
{
	mem->reg->pc += (char)read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x19
int add_hl_de(t_mem *mem)
{
	opcodes_add_hl(mem->reg->de, mem);
	return (1);
}

// 0x1a
int ld_a_ade(t_mem *mem)
{
	mem->reg->a = read(mem->reg->de, mem);
	return (1);
}

// 0x1b
int dec_de(t_mem *mem)
{
	mem->reg->de--;
	return (1);
}

// 0x1c
int inc_e(t_mem *mem)
{
	opcodes_inc((unsigned char*)&mem->reg->de, mem);
	return (1);
}

// 0x1d
int dec_e(t_mem *mem)
{
	opcodes_dec((unsigned char*)&mem->reg->de, mem);
	return (1);
}

// 0x1e
int ld_e_d8(t_mem *mem)
{
	mem->reg->de = (mem->reg->de & 0xff00) + read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x1f
int rra(t_mem *mem)
{
	opcodes_rr(&mem->reg->a, mem);
	return (1);
}

// 0x20
int jr_nz_s8(t_mem *mem)
{
	if (CHECK_FLAG(7) == 0)
		mem->reg->pc += (char)read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x21
int ld_hl_d16(t_mem *mem)
{
	mem->reg->hl = read(mem->reg->pc + 1, mem);
	mem->reg->hl += read(mem->reg->pc + 2, mem) << 8;
	return (3);
}

// 0x22
int ld_ahlp_a(t_mem *mem)
{
	write(mem->reg->hl++, mem->reg->a, mem);
	return (1);
}

// 0x23
int inc_hl(t_mem *mem)
{
	mem->reg->hl++;
	return (1);
}

// 0x24
int inc_h(t_mem *mem)
{
	opcodes_inc((unsigned char*)&mem->reg->hl + 1, mem);
	return (1);
}

// 0x25
int dec_h(t_mem *mem)
{
	opcodes_dec((unsigned char*)&mem->reg->hl + 1, mem);
	return (1);
}

// 0x26
int ld_h_d8(t_mem *mem)
{
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (read(mem->reg->pc + 1, mem) << 8);
	return (2);
}

// 0x27
int daa(t_mem *mem)
{
	int a = mem->reg->a;
	if (!CHECK_FLAG(6))
	{
		if (CHECK_FLAG(5) || (a & 0xf) > 9)
			a += 0x6;
		if (CHECK_FLAG(4) || a > 0x9f)
			a += 0x60;
	}
	else
	{
		if (CHECK_FLAG(5))
			a = (a - 6) & 0xff;
		if (CHECK_FLAG(5))
			a -= 0x60;
	}
	CLEAR_FLAG(7);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	if ((a & 0x100) == 0x100)
		SET_FLAG(4);
	a &= 0xff;
	if (a == 0)
		SET_FLAG(7);
	mem->reg->a = a;
	return (1);
}

// 0x28
int jr_z_s8(t_mem *mem)
{
	if (CHECK_FLAG(7) == 1)
		mem->reg->pc += (char)read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x29
int add_hl_hl(t_mem *mem)
{
	opcodes_add_hl(mem->reg->hl, mem);
	return (1);
}

// 0x2a
int ld_a_ahlp(t_mem *mem)
{
	mem->reg->a = read(mem->reg->hl++, mem);
	return (1);
}

// 0x2b
int dec_hl(t_mem *mem)
{
	mem->reg->hl--;
	return (1);
}

// 0x2c
int inc_l(t_mem *mem)
{
	opcodes_inc((unsigned char*)&mem->reg->hl, mem);
	return (1);
}

// 0x2d
int dec_l(t_mem *mem)
{
	opcodes_dec((unsigned char*)&mem->reg->hl, mem);
	return (1);
}

// 0x2e
int ld_l_d8(t_mem *mem)
{
	mem->reg->hl = (mem->reg->hl & 0xff00) + read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x2f
int cpl(t_mem *mem)
{
	mem->reg->a = mem->reg->a ^ 0xff;
	SET_FLAG(6);
	SET_FLAG(5);
	return (1);
}

// 0x30
int jr_nc_s8(t_mem *mem)
{
	if (CHECK_FLAG(4) == 0)
		mem->reg->pc += (char)read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x31
int ld_sp_d16(t_mem *mem)
{
	mem->reg->sp = read(mem->reg->pc + 1, mem);
	mem->reg->sp += read(mem->reg->pc + 2, mem) << 8;
	return (3);
}

// 0x32
int ld_ahln_a(t_mem *mem)
{
	write(mem->reg->hl--, mem->reg->a, mem);
	return (1);
}

// 0x33
int inc_sp(t_mem *mem)
{
	mem->reg->sp++;
	return (1);
}

// 0x34
int inc_ahl(t_mem *mem)
{
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	unsigned char val = read(mem->reg->hl, mem);
	write(mem->reg->hl, ++val, mem);
	if (val == 0)
		SET_FLAG(7);
	if ((val & 0x0f) == 0x00)
		SET_FLAG(5);
	return (1);
}

// 0x35
int dec_ahl(t_mem *mem)
{
	CLEAR_FLAG(7);
	SET_FLAG(6);
	CLEAR_FLAG(5);
	unsigned char val = read(mem->reg->hl, mem);
	write(mem->reg->hl, --val, mem);
	if (val == 0)
		SET_FLAG(7);
	if ((val & 0x0f) == 0x00)
		SET_FLAG(5);
	return (1);
}

// 0x36
int ld_ahl_d8(t_mem *mem)
{
	write(mem->reg->hl, read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0x37
int scf(t_mem *mem)
{
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	SET_FLAG(4);
	return (1);
}

// 0x38
int jr_c_s8(t_mem *mem)
{
	if (CHECK_FLAG(4) == 1)
		mem->reg->pc += (char)read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x39
int add_hl_sp(t_mem *mem)
{
	opcodes_add_hl(mem->reg->sp, mem);
	return (1);
}

// 0x3a
int ld_a_ahln(t_mem *mem)
{
	mem->reg->a = read(mem->reg->hl--, mem);
	return (1);
}

// 0x3b
int dec_sp(t_mem *mem)
{
	mem->reg->sp--;
	return (1);
}

// 0x3c
int inc_a(t_mem *mem)
{
	opcodes_inc(&mem->reg->a, mem);
	return (1);
}

// 0x3d
int dec_a(t_mem *mem)
{
	opcodes_dec(&mem->reg->a, mem);
	return (1);
}

// 0x3e
int ld_a_d8(t_mem *mem)
{
	mem->reg->a = read(mem->reg->pc + 1, mem);
	return (2);
}

// 0x3f
int ccf(t_mem *mem)
{
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (CHECK_FLAG(4))
		CLEAR_FLAG(4);
	else
		SET_FLAG(4);
	return (1);
}

// 0x40
int ld_b_b(t_mem *mem)
{
	mem->reg->bc = (mem->reg->bc & 0xff00) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x41
int ld_b_c(t_mem *mem)
{
	mem->reg->bc = ((mem->reg->bc & 0x00ff) << 8) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x42
int ld_b_d(t_mem *mem)
{
	mem->reg->bc = (mem->reg->de & 0xff00) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x43
int ld_b_e(t_mem *mem)
{
	mem->reg->bc = ((mem->reg->de & 0x00ff) << 8) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x44
int ld_b_h(t_mem *mem)
{
	mem->reg->bc = (mem->reg->hl & 0xff00) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x45
int ld_b_l(t_mem *mem)
{
	mem->reg->bc = ((mem->reg->hl & 0x00ff) << 8) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x46
int ld_b_ahl(t_mem *mem)
{
	mem->reg->bc = (read(mem->reg->hl, mem) << 8) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x47
int ld_b_a(t_mem *mem)
{
	mem->reg->bc = (mem->reg->a << 8) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x48
int ld_c_b(t_mem *mem)
{
	mem->reg->bc = (mem->reg->bc & 0xff00) + ((mem->reg->bc & 0xff00) >> 8);
	return (1);
}

// 0x49
int ld_c_c(t_mem *mem)
{
	mem->reg->bc = (mem->reg->bc & 0xff00) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x4a
int ld_c_d(t_mem *mem)
{
	mem->reg->bc = ((mem->reg->de & 0xff00) >> 8) + (mem->reg->bc & 0xff00);
	return (1);
}

// 0x4b
int ld_c_e(t_mem *mem)
{
	mem->reg->bc = (mem->reg->de & 0x00ff) + (mem->reg->bc & 0xff00);
	return (1);
}

// 0x4c
int ld_c_h(t_mem *mem)
{
	mem->reg->bc = ((mem->reg->hl & 0xff00) >> 8) + (mem->reg->bc & 0xff00);
	return (1);
}

// 0x4d
int ld_c_l(t_mem *mem)
{
	mem->reg->bc = (mem->reg->hl & 0x00ff) + (mem->reg->bc & 0xff00);
	return (1);
}

// 0x4e
int ld_c_ahl(t_mem *mem)
{
	mem->reg->bc = read(mem->reg->hl, mem) + (mem->reg->bc & 0xff00);
	return (1);
}

// 0x4f
int ld_c_a(t_mem *mem)
{
	mem->reg->bc = mem->reg->a + (mem->reg->bc & 0xff00);
	return (1);
}

// 0x50
int ld_d_b(t_mem *mem)
{
	mem->reg->de = (mem->reg->bc & 0xff00) + (mem->reg->de & 0x00ff);
	return (1);
}

// 0x51
int ld_d_c(t_mem *mem)
{
	mem->reg->de = ((mem->reg->bc & 0x00ff) << 8) + (mem->reg->de & 0x00ff);
	return (1);
}

// 0x52
int ld_d_d(t_mem *mem)
{
	mem->reg->de = (mem->reg->de & 0xff00) + (mem->reg->de & 0x00ff);
	return (1);
}

// 0x53
int ld_d_e(t_mem *mem)
{
	mem->reg->de = ((mem->reg->de & 0x00ff) << 8) + (mem->reg->de & 0x00ff);
	return (1);
}

// 0x54
int ld_d_h(t_mem *mem)
{
	mem->reg->de = (mem->reg->hl & 0xff00) + (mem->reg->de & 0x00ff);
	return (1);
}

// 0x55
int ld_d_l(t_mem *mem)
{
	mem->reg->de = ((mem->reg->hl & 0x00ff) << 8) + (mem->reg->de & 0x00ff);
	return (1);
}

// 0x56
int ld_d_ahl(t_mem *mem)
{
	mem->reg->de = (read(mem->reg->hl, mem) << 8) + (mem->reg->de & 0x00ff);
	return (1);
}

// 0x57
int ld_d_a(t_mem *mem)
{
	mem->reg->de = (mem->reg->a << 8) + (mem->reg->de & 0x00ff);
	return (1);
}

// 0x58
int ld_e_b(t_mem *mem)
{
	mem->reg->de = (mem->reg->de & 0xff00) + ((mem->reg->de & 0xff00) >> 8);
	return (1);
}

// 0x59
int ld_e_c(t_mem *mem)
{
	mem->reg->de = (mem->reg->de & 0xff00) + (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x5a
int ld_e_d(t_mem *mem)
{
	mem->reg->de = ((mem->reg->de & 0xff00) >> 8) + (mem->reg->de & 0xff00);
	return (1);
}

// 0x5b
int ld_e_e(t_mem *mem)
{
	mem->reg->de = (mem->reg->de & 0x00ff) + (mem->reg->de & 0xff00);
	return (1);
}

// 0x5c
int ld_e_h(t_mem *mem)
{
	mem->reg->de = ((mem->reg->hl & 0xff00) >> 8) + (mem->reg->de & 0xff00);
	return (1);
}

// 0x5d
int ld_e_l(t_mem *mem)
{
	mem->reg->de = (mem->reg->hl & 0x00ff) + (mem->reg->de & 0xff00);
	return (1);
}

// 0x5e
int ld_e_ahl(t_mem *mem)
{
	mem->reg->de = read(mem->reg->hl, mem) + (mem->reg->de & 0xff00);
	return (1);
}

// 0x5f
int ld_e_a(t_mem *mem)
{
	mem->reg->de = mem->reg->a + (mem->reg->de & 0xff00);
	return (1);
}

// 0x60
int ld_h_b(t_mem *mem)
{
	mem->reg->hl = (mem->reg->bc & 0xff00) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x61
int ld_h_c(t_mem *mem)
{
	mem->reg->hl = ((mem->reg->bc & 0x00ff) << 8) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x62
int ld_h_d(t_mem *mem)
{
	mem->reg->hl = (mem->reg->de & 0xff00) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x63
int ld_h_e(t_mem *mem)
{
	mem->reg->hl = ((mem->reg->de & 0x00ff) << 8) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x64
int ld_h_h(t_mem *mem)
{
	mem->reg->hl = (mem->reg->hl & 0xff00) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x65
int ld_h_l(t_mem *mem)
{
	mem->reg->hl = ((mem->reg->hl & 0x00ff) << 8) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x66
int ld_h_ahl(t_mem *mem)
{
	mem->reg->hl = (read(mem->reg->hl, mem) << 8) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x67
int ld_h_a(t_mem *mem)
{
	mem->reg->hl = (mem->reg->a << 8) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x68
int ld_l_b(t_mem *mem)
{
	mem->reg->hl = (mem->reg->bc & 0xff00) + ((mem->reg->hl & 0xff00) >> 8);
	return (1);
}

// 0x69
int ld_l_c(t_mem *mem)
{
	mem->reg->hl = (mem->reg->bc & 0xff00) + (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x6a
int ld_l_d(t_mem *mem)
{
	mem->reg->hl = ((mem->reg->de & 0xff00) >> 8) + (mem->reg->hl & 0xff00);
	return (1);
}

// 0x6b
int ld_l_e(t_mem *mem)
{
	mem->reg->hl = (mem->reg->de & 0x00ff) + (mem->reg->hl & 0xff00);
	return (1);
}

// 0x6c
int ld_l_h(t_mem *mem)
{
	mem->reg->hl = ((mem->reg->hl & 0xff00) >> 8) + (mem->reg->hl & 0xff00);
	return (1);
}

// 0x6d
int ld_l_l(t_mem *mem)
{
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (mem->reg->hl & 0xff00);
	return (1);
}

// 0x6e
int ld_l_ahl(t_mem *mem)
{
	mem->reg->hl = read(mem->reg->hl, mem) + (mem->reg->hl & 0xff00);
	return (1);
}

// 0x6f
int ld_l_a(t_mem *mem)
{
	mem->reg->hl = mem->reg->a + (mem->reg->hl & 0xff00);
	return (1);
}

// 0x70
int ld_ahl_b(t_mem *mem)
{
	write(mem->reg->hl, (mem->reg->bc & 0xff00) >> 8, mem);
	return (1);
}

// 0x71
int ld_ahl_c(t_mem *mem)
{
	write(mem->reg->hl, (mem->reg->bc & 0x00ff), mem);
	return (1);
}

// 0x72
int ld_ahl_d(t_mem *mem)
{
	write(mem->reg->hl, (mem->reg->de & 0xff00) >> 8, mem);
	return (1);
}

// 0x73
int ld_ahl_e(t_mem *mem)
{
	write(mem->reg->hl, (mem->reg->de & 0x00ff), mem);
	return (1);
}

// 0x74
int ld_ahl_h(t_mem *mem)
{
	write(mem->reg->hl, (mem->reg->hl & 0xff00) >> 8, mem);
	return (1);
}

// 0x75
int ld_ahl_l(t_mem *mem)
{
	write(mem->reg->hl, (mem->reg->hl & 0x00ff), mem);
	return (1);
}

// 0x76
int halt(t_mem *mem)
{
	mem->halt = 1;
	return (1);
}

// 0x77
int ld_ahl_a(t_mem *mem)
{
	write(mem->reg->hl, mem->reg->a, mem);
	return (1);
}

// 0x78
int ld_a_b(t_mem *mem)
{
	mem->reg->a = (mem->reg->bc & 0xff00) >> 8;
	return (1);
}

// 0x79
int ld_a_c(t_mem *mem)
{
	mem->reg->a = (mem->reg->bc & 0x00ff);
	return (1);
}

// 0x7a
int ld_a_d(t_mem *mem)
{
	mem->reg->a = ((mem->reg->de & 0xff00) >> 8);
	return (1);
}

// 0x7b
int ld_a_e(t_mem *mem)
{
	mem->reg->a = (mem->reg->de & 0x00ff);
	return (1);
}

// 0x7c
int ld_a_h(t_mem *mem)
{
	mem->reg->a = ((mem->reg->hl & 0xff00) >> 8);
	return (1);
}

// 0x7d
int ld_a_l(t_mem *mem)
{
	mem->reg->a = (mem->reg->hl & 0x00ff);
	return (1);
}

// 0x7e
int ld_a_ahl(t_mem *mem)
{
	mem->reg->a = read(mem->reg->hl, mem);
	return (1);
}

// 0x7f
int ld_a_a(t_mem *mem)
{
	mem->reg->a = mem->reg->a;
	return (1);
}

// 0x80
int add_a_b(t_mem *mem)
{
	opcodes_add(*((unsigned char*)&mem->reg->bc + 1), mem);
	return (1);
}

// 0x81
int add_a_c(t_mem *mem)
{
	opcodes_add(*(unsigned char*)&mem->reg->bc, mem);
	return (1);
}

// 0x82
int add_a_d(t_mem *mem)
{
	opcodes_add(*((unsigned char*)&mem->reg->de + 1), mem);
	return (1);
}

// 0x83
int add_a_e(t_mem *mem)
{
	opcodes_add(*(unsigned char*)&mem->reg->de, mem);
	return (1);
}

// 0x84
int add_a_h(t_mem *mem)
{
	opcodes_add(*((unsigned char*)&mem->reg->hl + 1), mem);
	return (1);
}

// 0x85
int add_a_l(t_mem *mem)
{
	opcodes_add(*(unsigned char*)&mem->reg->hl, mem);
	return (1);
}

// 0x86
int add_a_ahl(t_mem *mem)
{
	opcodes_add(read(mem->reg->hl, mem), mem);
	return (1);
}

// 0x87
int add_a_a(t_mem *mem)
{
	opcodes_add(mem->reg->a, mem);
	return (1);
}

// 0x88
int adc_a_b(t_mem *mem)
{
	opcodes_adc(*((unsigned char*)&mem->reg->bc + 1), mem);
    return (1);
}

// 0x89
int adc_a_c(t_mem *mem)
{
	opcodes_adc(*(unsigned char*)&mem->reg->bc, mem);
	return (1);
}

// 0x8a
int adc_a_d(t_mem *mem)
{
	opcodes_adc(*((unsigned char*)&mem->reg->de + 1), mem);
	return (1);
}

// 0x8b
int adc_a_e(t_mem *mem)
{
	opcodes_adc(*(unsigned char*)&mem->reg->de, mem);
	return (1);
}

// 0x8c
int adc_a_h(t_mem *mem)
{
	opcodes_adc(*((unsigned char*)&mem->reg->hl + 1), mem);
	return (1);
}

// 0x8d
int adc_a_l(t_mem *mem)
{
	opcodes_adc(*(unsigned char*)&mem->reg->hl, mem);
	return (1);
}

// 0x8e
int adc_a_ahl(t_mem *mem)
{
	opcodes_adc(read(mem->reg->hl, mem), mem);
	return (1);
}

// 0x8f
int adc_a_a(t_mem *mem)
{
	opcodes_adc(mem->reg->a, mem);
	return (1);
}

// 0x90
int sub_b(t_mem *mem)
{
	opcodes_sub(*((unsigned char*)&mem->reg->bc + 1), mem);
	return (1);
}

// 0x91
int sub_c(t_mem *mem)
{
	opcodes_sub(*(unsigned char*)&mem->reg->bc, mem);
	return (1);
}

// 0x92
int sub_d(t_mem *mem)
{
	opcodes_sub(*((unsigned char*)&mem->reg->de + 1), mem);
	return (1);
}

// 0x93
int sub_e(t_mem *mem)
{
	opcodes_sub(*(unsigned char*)&mem->reg->de, mem);
	return (1);
}

// 0x94
int sub_h(t_mem *mem)
{
	opcodes_sub(*((unsigned char*)&mem->reg->hl + 1), mem);
	return (1);
}

// 0x95
int sub_l(t_mem *mem)
{
	opcodes_sub(*(unsigned char*)&mem->reg->hl, mem);
	return (1);
}

// 0x96
int sub_ahl(t_mem *mem)
{
	opcodes_sub(read(mem->reg->hl, mem), mem);
	return (1);
}

// 0x97
int sub_a(t_mem *mem)
{
	opcodes_sub(mem->reg->a, mem);
	return (1);
}

// 0x98
int sdc_a_b(t_mem *mem)
{
	opcodes_sbc(*((unsigned char*)&mem->reg->bc + 1), mem);
	return (1);
}

// 0x99
int sdc_a_c(t_mem *mem)
{
	opcodes_sbc(*(unsigned char*)&mem->reg->bc, mem);
	return (1);
}

// 0x9a
int sdc_a_d(t_mem *mem)
{
	opcodes_sbc(*((unsigned char*)&mem->reg->de + 1), mem);
	return (1);
}

// 0x9b
int sdc_a_e(t_mem *mem)
{
	opcodes_sbc(*(unsigned char*)&mem->reg->de, mem);
	return (1);
}

// 0x9c
int sdc_a_h(t_mem *mem)
{
	opcodes_sbc(*((unsigned char*)&mem->reg->hl + 1), mem);
	return (1);
}

// 0x9d
int sdc_a_l(t_mem *mem)
{
	opcodes_sbc(*(unsigned char*)&mem->reg->hl, mem);
	return (1);
}

// 0x9e
int sdc_a_ahl(t_mem *mem)
{
	opcodes_sbc(read(mem->reg->hl, mem), mem);
	return (1);
}

// 0x9f
int sdc_a_a(t_mem *mem)
{
	opcodes_sbc(mem->reg->a, mem);
	return (1);
}

// 0xa0
int and_b(t_mem *mem)
{
	and_x(mem->reg->bc >> 8, mem);
	return (1);
}

// 0xa1
int and_c(t_mem *mem)
{
	and_x(mem->reg->bc & 0x00ff, mem);
	return (1);
}

// 0xa2
int and_d(t_mem *mem)
{
	and_x(mem->reg->de >> 8, mem);
	return (1);
}

// 0xa3
int and_e(t_mem *mem)
{
	and_x(mem->reg->de & 0x00ff, mem);
	return (1);
}

// 0xa4
int and_h(t_mem *mem)
{
	and_x(mem->reg->hl >> 8, mem);
	return (1);
}

// 0xa5
int and_l(t_mem *mem)
{
	and_x(mem->reg->hl & 0x00ff, mem);
	return (1);
}

// 0xa6
int and_ahl(t_mem *mem)
{
	and_x(read(mem->reg->hl, mem), mem);
	return (1);
}

// 0xa7
int and_a(t_mem *mem)
{
	and_x(mem->reg->a, mem);
	return (1);
}

// 0xa8
int xor_b(t_mem *mem)
{
	xor_x(mem->reg->bc >> 8, mem);
	return (1);
}

// 0xa9
int xor_c(t_mem *mem)
{
	xor_x(mem->reg->bc & 0x00ff, mem);
	return (1);
}

// 0xaa
int xor_d(t_mem *mem)
{
	xor_x(mem->reg->de >> 8, mem);
	return (1);
}

// 0xab
int xor_e(t_mem *mem)
{
	xor_x(mem->reg->de & 0x00ff, mem);
	return (1);
}

// 0xac
int xor_h(t_mem *mem)
{
	xor_x(mem->reg->hl >> 8, mem);
	return (1);
}

// 0xad
int xor_l(t_mem *mem)
{
	xor_x(mem->reg->hl & 0x00ff, mem);
	return (1);
}

// 0xae
int xor_ahl(t_mem *mem)
{
	xor_x(read(mem->reg->hl, mem), mem);
	return (1);
}

// 0xaf
int xor_a(t_mem *mem)
{
	xor_x(mem->reg->a, mem);
	return (1);
}

// 0xb0
int or_b(t_mem *mem)
{
	or_x(mem->reg->bc >> 8, mem);
	return (1);
}

// 0xb1
int or_c(t_mem *mem)
{
	or_x(mem->reg->bc & 0x00ff, mem);
	return (1);
}

// 0xb2
int or_d(t_mem *mem)
{
	or_x(mem->reg->de >> 8, mem);
	return (1);
}

// 0xb3
int or_e(t_mem *mem)
{
	or_x(mem->reg->de & 0x00ff, mem);
	return (1);
}

// 0xb4
int or_h(t_mem *mem)
{
	or_x(mem->reg->hl >> 8, mem);
	return (1);
}

// 0xb5
int or_l(t_mem *mem)
{
	or_x(mem->reg->hl & 0x00ff, mem);
	return (1);
}

// 0xb6
int or_ahl(t_mem *mem)
{
	or_x(read(mem->reg->hl, mem), mem);
	return (1);
}

// 0xb7
int or_a(t_mem *mem)
{
	or_x(mem->reg->a, mem);
	return (1);
}

// 0xb8
int cp_b(t_mem *mem)
{
	cp_x(mem->reg->bc >> 8, mem);
	return (1);
}

// 0xb9
int cp_c(t_mem *mem)
{
	cp_x(mem->reg->bc & 0x00ff, mem);
	return (1);
}

// 0xba
int cp_d(t_mem *mem)
{
	cp_x(mem->reg->de >> 8, mem);
	return (1);
}

// 0xbb
int cp_e(t_mem *mem)
{
	cp_x(mem->reg->de & 0x00ff, mem);
	return (1);
}

// 0xbc
int cp_h(t_mem *mem)
{
	cp_x(mem->reg->hl >> 8, mem);
	return (1);
}

// 0xbd
int cp_l(t_mem *mem)
{
	cp_x(mem->reg->hl & 0x00ff, mem);
	return (1);
}

// 0xbe
int cp_ahl(t_mem *mem)
{
	cp_x(read(mem->reg->hl, mem), mem);
	return (1);
}

// 0xbf
int cp_a(t_mem *mem)
{
	cp_x(mem->reg->a, mem);
	return (1);
}

// 0xc0
int ret_nz(t_mem *mem)
{
	if (CHECK_FLAG(7) == 0)
	{
		mem->reg->pc = read(mem->reg->sp++, mem);
		mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
		return (0);
	}
	return (1);
}

// 0xc1
int pop_bc(t_mem *mem)
{
	mem->reg->bc = read(mem->reg->sp++, mem);
	mem->reg->bc += read(mem->reg->sp++, mem) << 8;
	return (1);
}

// 0xc2
int jp_nz_a16(t_mem *mem)
{
	if (CHECK_FLAG(7) == 0)
		mem->reg->pc = (read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8)) - 3;
	return (3);
}

// 0xc3
int jp_a16(t_mem *mem)
{
	mem->reg->pc = read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8);
	return (0);
}

// 0xc4
int call_nz(t_mem *mem)
{
	unsigned short val;
	if (CHECK_FLAG(7) == 0)
	{
		write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
		write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
		val = read(mem->reg->pc + 1, mem);
		val += read(mem->reg->pc + 2, mem) << 8;
		mem->reg->pc = val;
		return (0);
	}
	return (3);
}

// 0xc5
int push_bc(t_mem *mem)
{
    unsigned short val;
    write(--mem->reg->sp, (mem->reg->bc >> 8) & 0xff, mem);
    write(--mem->reg->sp, mem->reg->bc & 0xff, mem);
    return (1);
}

// 0xc6
int add_a_d8(t_mem *mem)
{
	opcodes_add(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xc7
int rst_00(t_mem *mem)
{
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x00;
	return (0);
}

// 0xc8
int ret_z(t_mem *mem)
{
	if (CHECK_FLAG(7) == 1)
	{
		mem->reg->pc = read(mem->reg->sp++, mem);
		mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
		return (0);
	}
	return (1);
}

// 0xc9
int ret(t_mem *mem)
{
	unsigned short val;
	mem->reg->pc = read(mem->reg->sp++, mem);
	mem->reg->pc += read(mem->reg->sp++, mem) << 8;
	return (0);
}

// 0xca
int jp_z_a16(t_mem *mem)
{
	if (CHECK_FLAG(7) == 1)
		mem->reg->pc = (read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8)) - 3;
	return (3);
}

// 0xcb
int op_cb(t_mem *mem)
{
	mem->last_cycle = g_cb_cycle[read(mem->reg->pc + 1, mem)];
	return (g_bit_tab[read(mem->reg->pc + 1, mem)].f(mem));
}

// 0xcc
int call_z(t_mem *mem)
{
	unsigned short val;
	if (CHECK_FLAG(7) == 1)
	{
		write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
		write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
		val = read(mem->reg->pc + 1, mem);
		val += read(mem->reg->pc + 2, mem) << 8;
		mem->reg->pc = val;
		return (0);
	}
	return (3);
}

// 0xcd
int call_a16(t_mem *mem)
{
	unsigned short val;
	write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
	write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
	val = read(mem->reg->pc + 1, mem);
	val += read(mem->reg->pc + 2, mem) << 8;
	mem->reg->pc = val;
	return (0);
}

// 0xce
int adc_a_d8(t_mem *mem)
{
	opcodes_adc(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xcf
int rst_08(t_mem *mem)
{
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x08;
	return (0);
}

// 0xd0
int ret_nc(t_mem *mem)
{
	if (CHECK_FLAG(4) == 0)
	{
		mem->reg->pc = read(mem->reg->sp++, mem);
		mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
		return (0);
	}
	return (1);
}

// 0xd1
int pop_de(t_mem *mem)
{
	mem->reg->de = read(mem->reg->sp++, mem);
	mem->reg->de += read(mem->reg->sp++, mem) << 8;
	return (1);
}

// 0xd2
int jp_nc_a16(t_mem *mem)
{
	if (CHECK_FLAG(4) == 0)
		mem->reg->pc = (read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8)) - 3;
	return (3);
}

// 0xd4
int call_nc(t_mem *mem)
{
	unsigned short val;
	if (CHECK_FLAG(4) == 0)
	{
		write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
		write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
		val = read(mem->reg->pc + 1, mem);
		val += read(mem->reg->pc + 2, mem) << 8;
		mem->reg->pc = val;
		return (0);
	}
	return (3);
}

// 0xd5
int push_de(t_mem *mem)
{
	unsigned short val;
	write(--mem->reg->sp, (mem->reg->de >> 8) & 0xff, mem);
	write(--mem->reg->sp, mem->reg->de & 0xff, mem);
	return (1);
}

// 0xd6
int sub_d8(t_mem *mem)
{
	opcodes_sub(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xd7
int rst_10(t_mem *mem)
{
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x10;
	return (0);
}

// 0xd8
int ret_c(t_mem *mem)
{
	if (CHECK_FLAG(4) == 1)
	{
		mem->reg->pc = read(mem->reg->sp++, mem);
		mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
		return (0);
	}
	return (1);
}

// 0xd9
int reti(t_mem *mem)
{
	mem->reg->pc = read(mem->reg->sp++, mem);
	mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
	mem->master_interrupt = 1;
	return (1);
}

// 0xda
int jp_c_a16(t_mem *mem)
{
	if (CHECK_FLAG(4) == 1)
		mem->reg->pc = (read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8)) - 3;
	return (3);
}

// 0xdc
int call_c(t_mem *mem)
{
	unsigned short val;
	if (CHECK_FLAG(4) == 1)
	{
		write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
		write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
		val = read(mem->reg->pc + 1, mem);
		val += read(mem->reg->pc + 2, mem) << 8;
		mem->reg->pc = val;
		return (0);
	}
	return (3);
}

// 0xde
int sdc_a_d8(t_mem *mem)
{
	opcodes_sbc(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xdf
int rst_18(t_mem *mem)
{
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x18;
	return (0);
}

// 0xe0
int ld_ad8_a(t_mem *mem)
{
	unsigned char val = read(mem->reg->pc + 1, mem);
	write(val + 0xff00, mem->reg->a, mem);
	return (2);
}

// 0xe1
int pop_hl(t_mem *mem)
{
	mem->reg->hl = read(mem->reg->sp++, mem);
	mem->reg->hl += read(mem->reg->sp++, mem) << 8;
	return (1);
}

// 0xe2
int ld_ac_a(t_mem *mem)
{
	unsigned char val = (unsigned char)(mem->reg->bc & 0xff);
	write(val + 0xff00, mem->reg->a, mem);
	return (1);
}

// 0xe5
int push_hl(t_mem *mem)
{
	unsigned short val;
	write(--mem->reg->sp, (mem->reg->hl >> 8) & 0xff, mem);
	write(--mem->reg->sp, mem->reg->hl & 0xff, mem);
	return (1);
}

// 0xe6
int and_d8(t_mem *mem)
{
	and_x(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xe7
int rst_20(t_mem *mem)
{
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x20;
	return (0);
}

// 0xe8
int add_sp_s8(t_mem *mem)
{
	opcodes_add_sp(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xe9
int jp_ahl(t_mem *mem)
{
	mem->reg->pc = mem->reg->hl;
	return (0);
}

// 0xea
int ld_ad16_a(t_mem *mem)
{
	unsigned short addr;
	addr = (read(mem->reg->pc + 2, mem) << 8) + read(mem->reg->pc + 1, mem);
	write(addr, mem->reg->a, mem);
	return (3);
}

// 0xee
int xor_d8(t_mem *mem)
{
	xor_x(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xef
int rst_28(t_mem *mem)
{
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x28;
	return (0);
}

// 0xf0
int ld_a_ad8(t_mem *mem)
{
	unsigned short val = read(mem->reg->pc + 1, mem) + 0xff00;
	mem->reg->a = read(val, mem);
	return (2);
}

// 0xf1
int     pop_af(t_mem *mem)
{
	mem->reg->f = read(mem->reg->sp++, mem);
	mem->reg->a = read(mem->reg->sp++, mem);
	return (1);
}

// 0xf2
int ld_a_ac(t_mem *mem)
{
	mem->reg->a = read((mem->reg->bc & 0x00ff) + 0xff00, mem);
	return (2);
}

// 0xf3
int di(t_mem *mem)
{
	mem->master_interrupt = 0;
	return (1);
}

// 0xf5
int push_af(t_mem *mem)
{
	unsigned short val;
	write(--mem->reg->sp, mem->reg->a, mem);
	write(--mem->reg->sp, mem->reg->f, mem);
	return (1);
}

// 0xf6
int or_d8(t_mem *mem)
{
	or_x(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xf7
int rst_30(t_mem *mem)
{
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x30;
	return (0);
}

// 0xf8
int ld_hl_sp_s8(t_mem *mem)
{
	char val = read(mem->reg->pc + 1, mem);
	unsigned short res = mem->reg->sp + val;
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	if (((mem->reg->sp ^ val ^ res) & 0x10) == 0x10)
		SET_FLAG(5);
	if (((mem->reg->sp ^ val ^ res) & 0x100) == 0x100)
		SET_FLAG(4);
	mem->reg->hl = res;
	return (2);
}

// 0xf9
int ld_sp_hl(t_mem *mem)
{
	mem->reg->sp = mem->reg->hl;
	return (2);
}

// 0xfa
int ld_a_ad16(t_mem *mem)
{
	unsigned short addr = read(mem->reg->pc + 1, mem) + (read(mem->reg->pc + 2, mem) << 8);
	mem->reg->a = read(addr, mem);
	return (3);
}

// 0xfb
int ei(t_mem *mem)
{
	mem->master_interrupt = 1;
	return (1);
}

// 0xfe
int cp_d8(t_mem *mem)
{
	cp_x(read(mem->reg->pc + 1, mem), mem);
	return (2);
}

// 0xff
int rst_38(t_mem *mem)
{
	write(--mem->reg->sp, mem->reg->pc >> 8, mem);
	write(--mem->reg->sp, mem->reg->pc & 0xff, mem);
	mem->reg->pc = 0x38;
	return (0);
}

int empty(t_mem *mem)
{
	printf("HIT EMPTY instruction!!\n");
	exit(0);
    return (0);
}
