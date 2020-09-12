#include "define.h"
#include "z80.h"
#include "struct.h"
#include "op.h"

t_op	g_op_tab[OP_TAB_SIZE] =
{
	{op_nop}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {inc_c}, {not_done}, {ld_c_d8}, {not_done}, //0 -> f
	{not_done}, {ld_de_d16}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_a_ade}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //10 -> 1f
	{jr_nz_s8}, {ld_hl_d16}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //20 -> 2f
	{not_done}, {ld_sp_d16}, {ld_ahln_a}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_a_d8}, {not_done}, //30 -> 3f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //40 -> 4f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //50 -> 5f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //60 -> 6f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_ahl_a}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //70 -> 7f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //80 -> 8f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //90 -> 9f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {xor_a}, //a0 -> af
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //b0 -> bf
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {op_cb}, {not_done}, {not_done}, {not_done}, {not_done}, //c0 -> cf
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //d0 -> df
	{ld_ad8_a}, {not_done}, {ld_ac_a}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //e0 -> ef
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done} //f0 -> ff
};

t_op	g_bit_tab[OP_TAB_SIZE] =
{
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //0 -> f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //10 -> 1f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //20 -> 2f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //30 -> 3f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //40 -> 4f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //50 -> 5f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //60 -> 6f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {bit_7h}, {not_done}, {not_done}, {not_done}, //70 -> 7f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //80 -> 8f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //90 -> 9f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //a0 -> af
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //b0 -> bf
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //c0 -> cf
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //d0 -> df
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //e0 -> ef
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done} //f0 -> ff
};

int	op_cb(t_mem *mem)
{
	int size = -1;

	size = g_bit_tab[read(mem->reg->pc + 1, mem)].f(mem);
	return (size);
}

int	read_op_byte(t_mem *mem)
{
	int size = -1;

	size = g_op_tab[read(mem->reg->pc, mem)].f(mem);
	return (size);
}

void read_mem_bytes(t_mem *mem, int size)
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
