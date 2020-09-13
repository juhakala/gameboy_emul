#include "define.h"
#include "z80.h"
#include "struct.h"
#include "op.h"

t_op	g_op_tab[OP_TAB_SIZE] =
{
	{op_nop}, {ld_bc_d16}, {ld_abc_a}, {inc_bc}, {not_done}, {dec_b}, {ld_b_d8}, {not_done}, {not_done}, {not_done}, {ld_a_abc}, {not_done}, {inc_c}, {dec_c}, {ld_c_d8}, {not_done}, //0 -> f
	{not_done}, {ld_de_d16}, {ld_ade_a}, {inc_de}, {not_done}, {not_done}, {ld_d_d8}, {rla}, {jr_s8}, {not_done}, {ld_a_ade}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //10 -> 1f
	{jr_nz_s8}, {ld_hl_d16}, {ld_ahlp_a}, {inc_hl}, {not_done}, {not_done}, {not_done}, {not_done}, {jr_z_s8}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_l_d8}, {not_done}, //20 -> 2f
	{jr_nc_s8}, {ld_sp_d16}, {ld_ahln_a}, {inc_sp}, {not_done}, {not_done}, {not_done}, {not_done}, {jr_c_s8}, {not_done}, {not_done}, {not_done}, {not_done}, {dec_a}, {ld_a_d8}, {not_done}, //30 -> 3f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_c_a}, //40 -> 4f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //50 -> 5f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //60 -> 6f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_ahl_a}, {not_done}, {not_done}, {not_done}, {ld_a_e}, {not_done}, {not_done}, {not_done}, {not_done}, //70 -> 7f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //80 -> 8f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //90 -> 9f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {xor_a}, //a0 -> af
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //b0 -> bf
	{not_done}, {pop_bc}, {not_done}, {not_done}, {not_done}, {push_bc}, {not_done}, {not_done}, {not_done}, {ret}, {not_done}, {op_cb}, {not_done}, {call_a16}, {not_done}, {not_done}, //c0 -> cf
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //d0 -> df
	{ld_ad8_a}, {not_done}, {ld_ac_a}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_ad16_a}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //e0 -> ef
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {cp_d8}, {not_done} //f0 -> ff
};

t_op	g_bit_tab[OP_TAB_SIZE] =
{
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //0 -> f
	{not_done}, {rl_c}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //10 -> 1f
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
