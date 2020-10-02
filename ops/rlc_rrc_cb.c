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

// 0x00
int     rlc_b(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RLC", "B", 2, mem);
	c = mem->reg->bc & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1) + (c >> 7);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x01
int     rlc_c(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RLC", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1) + (c >> 7);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x02
int     rlc_d(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RLC", "D", 2, mem);
	c = mem->reg->de & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1) + (c >> 7);
	mem->reg->de = (mem->reg->de & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x03
int     rlc_e(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RLC", "E", 2, mem);
	c = mem->reg->de & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1) + (c >> 7);
	mem->reg->de = (mem->reg->de & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x04
int     rlc_h(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RLC", "H", 2, mem);
	c = mem->reg->hl & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1) + (c >> 7);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x05
int     rlc_l(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RLC", "L", 2, mem);
	c = mem->reg->hl & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1) + (c >> 7);
	mem->reg->hl = (mem->reg->hl & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x06
int     rlc_ahl(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RLC", "(HL)", 2, mem);
	c = read(mem->reg->hl, mem);
	carry = (c >> 7) & 1;
	c = (c << 1) + (c >> 7);
	write(mem->reg->hl, c, mem);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x07
int     rlc_a(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RLC", "A", 2, mem);
	c = mem->reg->a;
	carry = (c >> 7) & 1;
	c = (c << 1) + (c >> 7);
	mem->reg->a = c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x08
int     rrc_b(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RRC", "B", 2, mem);
	c = mem->reg->bc & 0xff00;
	carry = c & 1;
	c = (c >> 1) + ((c & 1) << 7);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x09
int     rrc_c(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RRC", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + ((c & 1) << 7);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x0a
int     rrc_d(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RRC", "D", 2, mem);
	c = mem->reg->de & 0xff00;
	carry = c & 1;
	c = (c >> 1) + ((c & 1) << 7);
	mem->reg->de = (mem->reg->de & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x0b
int     rrc_e(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RRC", "E", 2, mem);
	c = mem->reg->de & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + ((c & 1) << 7);
	mem->reg->de = (mem->reg->de & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x0c
int     rrc_h(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RRC", "H", 2, mem);
	c = mem->reg->hl & 0xff00;
	carry = c & 1;
	c = (c >> 1) + ((c & 1) << 7);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x0d
int     rrc_l(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RRC", "L", 2, mem);
	c = mem->reg->hl & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + ((c & 1) << 7);
	mem->reg->hl = (mem->reg->hl & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x0e
int     rrc_ahl(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RRC", "(HL)", 2, mem);
	c = read(mem->reg->hl, mem);
	carry = c & 1;
	c = (c >> 1) + ((c & 1) << 7);
	write(mem->reg->hl, c, mem);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x0f
int     rrc_a(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RRC", "A", 2, mem);
	c = mem->reg->a;
	carry = c & 1;
	c = (c >> 1) + ((c & 1) << 7);
	mem->reg->a = c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x10
int     rl_b(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "B", 2, mem);
	c = mem->reg->bc & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x11
int     rl_c(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x12
int     rl_d(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "D", 2, mem);
	c = mem->reg->de & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	mem->reg->de = (mem->reg->de & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x13
int     rl_e(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "E", 2, mem);
	c = mem->reg->de & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	mem->reg->de = (mem->reg->de & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x14
int     rl_h(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "H", 2, mem);
	c = mem->reg->hl & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x15
int     rl_l(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "L", 2, mem);
	c = mem->reg->hl & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	mem->reg->hl = (mem->reg->hl & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x16
int     rl_ahl(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "(HL)", 2, mem);
	c = read(mem->reg->hl, mem);
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	write(mem->reg->hl, c, mem);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x17
int     rl_a(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "A", 2, mem);
	c = mem->reg->a;
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	mem->reg->a = c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}


// 0x18
int     rr_b(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RR", "B", 2, mem);
	c = mem->reg->bc & 0xff00;
	carry = c & 1;
	c = (c >> 1) + (CHECK_FLAG(4) << 7);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x19
int     rr_c(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RR", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + (CHECK_FLAG(4) << 7);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x1a
int     rr_d(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RR", "D", 2, mem);
	c = mem->reg->de & 0xff00;
	carry = c & 1;
	c = (c >> 1) + (CHECK_FLAG(4) << 7);
	mem->reg->de = (mem->reg->de & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x1b
int     rr_e(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RR", "E", 2, mem);
	c = mem->reg->de & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + (CHECK_FLAG(4) << 7);
	mem->reg->de = (mem->reg->de & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x1c
int     rr_h(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RR", "H", 2, mem);
	c = mem->reg->hl & 0xff00;
	carry = c & 1;
	c = (c >> 1) + (CHECK_FLAG(4) << 7);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x1d
int     rr_l(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RR", "L", 2, mem);
	c = mem->reg->hl & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + (CHECK_FLAG(4) << 7);
	mem->reg->hl = (mem->reg->hl & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x1e
int     rr_ahl(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RR", "(HL)", 2, mem);
	c = read(mem->reg->hl, mem);
	carry = c & 1;
	c = (c >> 1) + (CHECK_FLAG(4) << 7);
	write(mem->reg->hl, c, mem);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x1f
int     rr_a(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RR", "A", 2, mem);
	c = mem->reg->a;
	carry = c & 1;
	c = (c >> 1) + (CHECK_FLAG(4) << 7);
	mem->reg->a = c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}


// 0x20
int     sla_b(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SLA", "B", 2, mem);
	c = mem->reg->bc & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x21
int     sla_c(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SLA", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x22
int     sla_d(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SLA", "D", 2, mem);
	c = mem->reg->de & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1);
	mem->reg->de = (mem->reg->de & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x23
int     sla_e(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SLA", "E", 2, mem);
	c = mem->reg->de & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1);
	mem->reg->de = (mem->reg->de & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x24
int     sla_h(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SLA", "H", 2, mem);
	c = mem->reg->hl & 0xff00;
	carry = (c >> 7) & 1;
	c = (c << 1);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x25
int     sla_l(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SLA", "L", 2, mem);
	c = mem->reg->hl & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1);
	mem->reg->hl = (mem->reg->hl & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x26
int     sla_ahl(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SLA", "(HL)", 2, mem);
	c = read(mem->reg->hl, mem);
	carry = (c >> 7) & 1;
	c = (c << 1);
	write(mem->reg->hl, c, mem);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x27
int     sla_a(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SLA", "A", 2, mem);
	c = mem->reg->a;
	carry = (c >> 7) & 1;
	c = (c << 1);
	mem->reg->a = c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x28
int     sra_b(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRA", "B", 2, mem);
	c = mem->reg->bc & 0xff00;
	carry = c & 1;
	c = (c >> 1) + (c & 128);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x29
int     sra_c(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRA", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + (c & 128);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x2a
int     sra_d(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRA", "D", 2, mem);
	c = mem->reg->de & 0xff00;
	carry = c & 1;
	c = (c >> 1) + (c & 128);
	mem->reg->de = (mem->reg->de & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x2b
int     sra_e(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRA", "E", 2, mem);
	c = mem->reg->de & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + (c & 128);
	mem->reg->de = (mem->reg->de & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x2c
int     sra_h(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRA", "H", 2, mem);
	c = mem->reg->hl & 0xff00;
	carry = c & 1;
	c = (c >> 1) + (c & 128);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x2d
int     sra_l(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRA", "L", 2, mem);
	c = mem->reg->hl & 0x00ff;
	carry = c & 1;
	c = (c >> 1) + (c & 128);
	mem->reg->hl = (mem->reg->hl & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x2e
int     sra_ahl(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRA", "(HL)", 2, mem);
	c = read(mem->reg->hl, mem);
	carry = c & 1;
	c = (c >> 1) + (c & 128);
	write(mem->reg->hl, c, mem);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x2f
int     sra_a(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRA", "A", 2, mem);
	c = mem->reg->a;
	carry = c & 1;
	c = (c >> 1) + (c & 128);
	mem->reg->a = c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}


// 0x30
int     swap_b(t_mem *mem)
{
	unsigned char c;

    if (PRINT)
        printing("SWAP", "B", 2, mem);
	c = mem->reg->bc & 0xff00;
	c = (c >> 4) + ((c & 0xf) << 4);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (2);
}

// 0x31
int     swap_c(t_mem *mem)
{
	unsigned char c;

    if (PRINT)
        printing("SWAP", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	c = (c >> 4) + ((c & 0xf) << 4);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (2);
}

// 0x32
int     swap_d(t_mem *mem)
{
	unsigned char c;

    if (PRINT)
        printing("SWAP", "D", 2, mem);
	c = mem->reg->de & 0xff00;
	c = (c >> 4) + ((c & 0xf) << 4);
	mem->reg->de = (mem->reg->de & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (2);
}

// 0x33
int     swap_e(t_mem *mem)
{
	unsigned char c;

    if (PRINT)
        printing("SWAP", "E", 2, mem);
	c = mem->reg->de & 0x00ff;
	c = (c >> 4) + ((c & 0xf) << 4);
	mem->reg->de = (mem->reg->de & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (2);
}

// 0x34
int     swap_h(t_mem *mem)
{
	unsigned char c;

    if (PRINT)
        printing("SWAP", "H", 2, mem);
	c = mem->reg->hl & 0xff00;
	c = (c >> 4) + ((c & 0xf) << 4);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (2);
}

// 0x35
int     swap_l(t_mem *mem)
{
	unsigned char c;

    if (PRINT)
        printing("SWAP", "L", 2, mem);
	c = mem->reg->hl & 0x00ff;
	c = (c >> 4) + ((c & 0xf) << 4);
	mem->reg->hl = (mem->reg->hl & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (2);
}

// 0x36
int     swap_ahl(t_mem *mem)
{
	unsigned char c;

    if (PRINT)
        printing("SWAP", "(HL)", 2, mem);
	c = read(mem->reg->hl, mem);
	c = (c >> 4) + ((c & 0xf) << 4);
	write(mem->reg->hl, c, mem);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (2);
}

// 0x37
int     swap_a(t_mem *mem)
{
	unsigned char c;

    if (PRINT)
        printing("SWAP", "A", 2, mem);
	c = mem->reg->a;
	c = (c >> 4) + ((c & 0xf) << 4);
	mem->reg->a = c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (2);
}

// 0x38
int     srl_b(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRL", "B", 2, mem);
	c = mem->reg->bc & 0xff00;
	carry = c & 1;
	c = (c >> 1);
	mem->reg->bc = (mem->reg->bc & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x39
int     srl_c(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRL", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	carry = c & 1;
	c = (c >> 1);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x3a
int     srl_d(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRL", "D", 2, mem);
	c = mem->reg->de & 0xff00;
	carry = c & 1;
	c = (c >> 1);
	mem->reg->de = (mem->reg->de & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x3b
int     srl_e(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRL", "E", 2, mem);
	c = mem->reg->de & 0x00ff;
	carry = c & 1;
	c = (c >> 1);
	mem->reg->de = (mem->reg->de & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x3c
int     srl_h(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRL", "H", 2, mem);
	c = mem->reg->hl & 0xff00;
	carry = c & 1;
	c = (c >> 1);
	mem->reg->hl = (mem->reg->hl & 0x00ff) + (c << 8);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x3d
int     srl_l(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRL", "L", 2, mem);
	c = mem->reg->hl & 0x00ff;
	carry = c & 1;
	c = (c >> 1);
	mem->reg->hl = (mem->reg->hl & 0xff00) + c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x3e
int     srl_ahl(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRL", "(HL)", 2, mem);
	c = read(mem->reg->hl, mem);
	carry = c & 1;
	c = (c >> 1);
	write(mem->reg->hl, c, mem);
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}

// 0x3f
int     srl_a(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("SRL", "A", 2, mem);
	c = mem->reg->a;
	carry = c & 1;
	c = (c >> 1);
	mem->reg->a = c;
	if (c == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	return (2);
}
