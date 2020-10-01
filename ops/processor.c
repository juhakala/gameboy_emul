#include "z80.h"
#include "struct.h"
#include "define.h"

int		g_op_cycle[OP_TAB_SIZE] = {
	4, 12, 8, 8, 4, 4, 8, 4, 20, 8, 8, 8, 4, 4, 8, 4,
	4, 12, 8, 8, 4, 4, 8, 4, 8, 8, 8, 8, 4, 4, 8, 4,
	8, 12, 8, 8, 4, 4, 8, 4, 8, 8, 8, 8, 4, 4, 8, 4,
	8, 12, 8, 8, 12, 12, 12, 4, 8, 8, 8, 8, 4, 4, 8, 4,
	4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
	4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
	4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
	8, 8, 8, 8, 8, 8, 4, 8, 4, 4, 4, 4, 4, 4, 8, 4,
	4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
	4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
	4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
	4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
	8, 12, 12, 12, 12, 16, 8, 32, 8, 8, 12, 0, 12, 12, 8, 32,
	8, 12, 12, 0, 12, 16, 8, 32, 8, 8, 12, 0, 12, 0, 8, 32,
	12, 12, 8, 0, 0, 16, 8, 32, 16, 4, 16, 0, 0, 0, 8, 32,
	12, 12, 8, 4, 0, 16, 8, 32, 12, 8, 16, 4, 0, 0, 8, 32
};

int		g_op_size[OP_TAB_SIZE] = {
	1, 3, 1, 1, 1, 1, 2, 1, 3, 1, 1, 1, 1, 1, 2, 1,
	2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
	2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
	2, 3, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 3, 3, 3, 1, 2, 2, 1, 1, 3, 0, 3, 3, 2, 2,
	1, 1, 3, 0, 3, 1, 2, 2, 1, 1, 3, 0, 3, 0, 2, 2,
	2, 1, 1, 0, 0, 1, 2, 2, 2, 1, 3, 0, 0, 0, 2, 2,
	2, 1, 2, 1, 0, 1, 2, 1, 2, 1, 3, 1, 0, 0, 2, 2
};

char	*g_op_str[OP_TAB_SIZE] = {
	"NOP",			"LD BC d16",	"LD (BC), A",		"INC BC",		"INC B",		"DEC B",	"LD B, d8",		"RLCA",		"LD (a16), SP",		"ADD HL, BC",	"LD A, (BC)",	"DEC BC",		"INC C",	"DEC C",		"LD C, d8",		"RRCA",
	"STOP",			"LD DE, d16",	"LD (DE), A",		"INC DE",		"INC D",		"DEC D",	"LD D, d8",		"RLA",		"JR s8 (r)",		"ADD HL, DE",	"LD A, (DE)", 	"DEC DE",		"INC E",	"DEC E",		"LD E, d8",		"RRA",
	"JR NZ, s8",	"LD HL, d16",	"LD (HL+), A",		"INC HL",		"INC H",		"DEC H",	"LD H, d8",		"DAA",		"JR Z, s8",			"ADD HL, HL",	"LD A, (HL+)",	"DEC HL",		"INC L",	"DEC L",		"LD L, d8",		"CPL",
	"JR NC, s8",	"LD SP, d16",	"LD (HL-), A",		"INC SP",		"INC (HL)",		"DEC (HL)",	"LD (HL), d8",	"SCF",		"JR C, s8",			"ADD HL, SP",	"LD A (HL-)",	"DEC SP",		"INC A",	"DEC A",		"LD A, d8",		"CCF",
	"LD B, B",		"LD B, C",		"LD B, D",			"LD B, E",		"LD B, H",		"LD B, L",	"LD B, (HL)",	"LD B, A",	"LD C, B",			"LD C, C",		"LD C, D",		"LD C, E",		"LD C, H",	"LD C, L",		"LD C, (HL)",	"LD C, A",
	"LD D, B",		"LD D, C",		"LD D, D",			"LD D, E",		"LD D, H",		"LD D, L",	"LD D, (HL)",	"LD D, A",	"LD E, B",			"LD E, C",		"LD E, D",		"LD E, E",		"LD E, H",	"LD E, L",		"LD E, (HL)",	"LD E, A",
	"LD H, B",		"LD H, C",		"LD H, D",			"LD H, E",		"LD H, H",		"LD H, L",	"LD H, (HL)",	"LD H, A",	"LD L, B",			"LD L, C",		"LD L, D",		"LD L, E",		"LD L, H",	"LD L, L",		"LD L, (HL)",	"LD L, A",
	"LD (HL), B",	"LD (HL), C",	"LD (HL), D",		"LD (HL), E",	"LD (HL), H",	"LD (HL), L", "HALT",		"LD (HL), A", "LD A, B",		"LD A, C",		"LD A, D",		"LD A, E",		"LD A, H",	"LD A, L",		"LD A, (HL)",	"LD A, A",
	"ADD A, B",		"ADD A, C",		"ADD A, D",			"ADD A, E",		"ADD A, H",		"ADD A, L",	"ADD A, (HL)",	"ADD A, A",	"ADC A, B",			"ADC A, C",		"ADC A, D",		"ADC A, E",		"ADC A, H",	"ADC A, L",		"ADC A, (HL)",	"ADC A, A",
	"SUB B",		"SUB C",		"SUB D",			"SUB E",		"SUB H",		"SUB L",	"SUB (HL)",		"SUB A",	"SBC A, B",			"SBC A, C",		"SBC A, D",		"SBC A, E",		"SBC A, H",	"SBC A, L",		"SBC A, (HL)",	"SBC A, A",
	"AND B",		"AND C",		"AND D",			"AND E",		"AND H",		"AND L",	"AND (HL)",		"AND A",	"XOR B",			"XOR C",		"XOR D",		"XOR E",		"XOR H",	"XOR L",		"XOR (HL)",		"XOR A",
	"OR B",			"OR C",			"OR D",				"OR E",			"OR H",			"OR L",		"OR (HL)",		"OR A",		"CP B",				"CP C",			"CP D",			"CP E",			"CP H",		"CP L",			"CP (HL)",		"CP A",
	"RET NZ",		"POP BC",		"JP NZ, a16",		"JP a16",		"CALL NZ",		"PUSH BC",	"ADD d8",		"RST 00H",	"RET Z",			"RET",			"JP Z, a16",	"",			"CALL Z, a16",	"CALL a16",		"ADC A, d8",	"RST 08H",
	"RET NC",		"POP DE",		"JP NC, a16",		"",				"CALL NC, a16",	"PUSH DE",	"SUB d8",		"RST 10H",	"RET C",			"RETI",			"JP C, a16",	"",			"CALL C, a16",	"",				"SBC A, d8",	"RST 18H",
	"LD ($FF00 + d8), A", "POP HL",	"($FF00 + C), A",	"", 			"",				"PUSH HL",	"AND d8",		"RST 20H",	"ADD SP, s8",		"JP (HL)",		"LD (d16), A",	"",				"",			"",				"XOR d8",		"RST 28H",
	"LD A, ($FF00 + d8)", "POP AF",	"LD A, ($FF00 + C)", "DI",			"",				"PUSH AF",	"OR d8",		"RST 30H",	"LD HL, SP + s8",	"LD SP, HL",	"LD A, (a16)",	"EI",			"",			"",				"CP d8",		"RST 38H", 
};

void	read_mem_bytes(t_mem *mem, int size)
{
	int i = 0;

	printf("[%u]		(0x%05hx -> 0x%05hx): ", mem->cycle, mem->reg->pc, (unsigned short)(mem->reg->pc + (size - 1)));
	while (i < size)
	{
		printf("%02hhx ", read(mem->reg->pc + i++, mem));
	}
	while (i++ < 5)
		printf("   ");
	printf("|");
}

	void	printing(char *str, int size, t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, size);
	if (PRINT & 2)
		printf("	%s", str);
	printf("\n");
}
	
int		read_op_byte(t_mem *mem)
{
	int size = -1;
	unsigned short val = read(mem->reg->pc, mem);

	if (PRINT)
		printing(g_op_str[val], g_op_size[val], mem);
	mem->last_cycle = g_op_cycle[val];
	mem->cycle += mem->last_cycle;
	size = g_op_tab[val].f(mem);
//	mem->over_all_cycle += mem->last_cycle;

	return (size);
}

void	opcodes_inc(unsigned char *reg, t_mem *mem)
{
	*reg += 1;

	if (*reg == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	if ((*reg & 0x0f) == 0)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
}

void	opcodes_dec(unsigned char *reg, t_mem *mem)
{
	*reg -= 1;

	CLEAR_FLAG(7);
	SET_FLAG(6);
	CLEAR_FLAG(5);
	if (*reg == 0)
		SET_FLAG(7);
	if ((*reg & 0x0f) == 0x0f)
		SET_FLAG(5);
}

void	opcodes_rlc(unsigned char *reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	if (((*reg >> 7) & 1) == 1)
		SET_FLAG(4);
	*reg = (*reg << 1) + CHECK_FLAG(4);
	if (*reg == 0)
		SET_FLAG(7);
}

void	opcodes_rrc(unsigned char *reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	if ((*reg & 1) == 1)
		SET_FLAG(4);
	*reg = (*reg >> 1) + (CHECK_FLAG(4) << 7);
	if (*reg == 0)
		SET_FLAG(7);
}

void	opcodes_rl(unsigned char *reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	int carry = 0;
	if (((*reg >> 7) & 1) == 1)
		carry = 1;
	*reg = (*reg << 1) + CHECK_FLAG(4);
	if (*reg == 0)
		SET_FLAG(7);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
}

void	opcodes_rr(unsigned char *reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	int carry = 0;
	if ((*reg & 1) == 1)
		carry = 1;
	*reg = (*reg >> 1) + (CHECK_FLAG(4) << 7);
	if (*reg == 0)
		SET_FLAG(7);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
}

void	opcodes_add_hl(unsigned short reg, t_mem *mem)
{
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	int val = mem->reg->hl + reg;
	if ((mem->reg->hl ^ reg ^ (val & 0xffff)) & 0x100)
		SET_FLAG(5);
	if (val & 0x10000)
		SET_FLAG(4);
	mem->reg->hl = (unsigned short)val;
}

void	opcodes_add_sp(unsigned char reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	int val = mem->reg->sp + reg;
	if (((mem->reg->sp ^ reg ^ (val & 0xffff)) & 0x10) == 0x10)
		SET_FLAG(5);
	if (((mem->reg->sp ^ reg ^ (val & 0xffff)) & 0x100) == 0x100)
		SET_FLAG(4);
	mem->reg->sp = (unsigned short)val;
}

void	opcodes_add(unsigned char reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	int val = mem->reg->a + reg;
	int carry = mem->reg->a ^ reg ^ val;
	mem->reg->a = val;
	if (mem->reg->a == 0)
		SET_FLAG(7);
	if ((carry & 0x10) != 0)
		SET_FLAG(5);
	if ((carry & 0x100) != 0)
		SET_FLAG(4);
}

void	opcodes_adc(unsigned char reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	int carry = CHECK_FLAG(4);
	int val = mem->reg->a + reg + carry;
	CLEAR_FLAG(4);
	if (val == 0)
		SET_FLAG(7);
	if (((mem->reg->a & 0x0f) + (reg & 0x0f) + carry)> 0x0f)
		SET_FLAG(5);
	if (val > 0xff)
		SET_FLAG(4);
	mem->reg->a = val;
}

void	opcodes_sub(unsigned char reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	SET_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	int val = mem->reg->a - reg;
	int carry = mem->reg->a ^ reg ^ val;
	if (val == 0)
		SET_FLAG(7);
	if ((carry & 0x100) != 0)
		SET_FLAG(5);
	if ((carry & 0x10) != 0)
		SET_FLAG(4);
	mem->reg->a = val;
}

void	opcodes_sbc(unsigned char reg, t_mem *mem)
{
	CLEAR_FLAG(7);
	SET_FLAG(6);
	CLEAR_FLAG(5);
	int carry = CHECK_FLAG(4);
	CLEAR_FLAG(4);
	int val = mem->reg->a - reg - carry;

	if (val == 0)
		SET_FLAG(7);
	if (((mem->reg->a & 0x0f) - (reg & 0x0f) - carry) < 0)
		SET_FLAG(5);
	if (val < 0)
		SET_FLAG(4);
	mem->reg->a = val;
}

void	and_x(unsigned char x, t_mem *mem)
{
	mem->reg->a &= x;
	if (mem->reg->a == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	SET_FLAG(5);
	CLEAR_FLAG(4);
}

void	xor_x(unsigned char x, t_mem *mem)
{
	mem->reg->a ^= x;
	if (mem->reg->a == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
}

void	or_x(unsigned char x, t_mem *mem)
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

void	cp_x(unsigned char x, t_mem *mem)
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
