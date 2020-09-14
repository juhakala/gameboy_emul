#include "define.h"
#include "z80.h"
#include "struct.h"
#include "op.h"

t_op	g_op_tab[OP_TAB_SIZE] =
{
	{op_nop},	{ld_bc_d16},	{ld_abc_a},		{inc_bc},	{inc_b},	{dec_b},	{ld_b_d8},	{rlca},		{ld_a16_sp},	{add_hl_bc},	{ld_a_abc},	{dec_bc},	{inc_c},	{dec_c},	{ld_c_d8},	{not_done}, //0 -> f
	{not_done},	{ld_de_d16},	{ld_ade_a},		{inc_de},	{inc_d},	{dec_d},	{ld_d_d8},	{rla},		{jr_s8},		{add_hl_de},	{ld_a_ade},	{dec_de},	{inc_e},	{not_done},	{not_done},	{not_done}, //10 -> 1f
	{jr_nz_s8},	{ld_hl_d16},	{ld_ahlp_a},	{inc_hl}, 	{inc_h},	{dec_h},	{ld_h_d8},	{not_done},	{jr_z_s8},		{add_hl_hl},	{not_done}, {dec_hl}, {inc_l}, {not_done}, {ld_l_d8}, {not_done}, //20 -> 2f
	{jr_nc_s8},	{ld_sp_d16},	{ld_ahln_a}, 	{inc_sp}, 	{not_done}, {not_done}, {not_done}, {scf},		{jr_c_s8},		{add_hl_sp},	{not_done}, {dec_sp}, {not_done}, {dec_a}, {ld_a_d8}, {not_done}, //30 -> 3f
	{ld_b_b}, {ld_b_c}, {ld_b_d}, {ld_b_e}, {ld_b_h}, {ld_b_l}, {ld_b_ahl}, {ld_b_a}, {ld_c_b}, {ld_c_c}, {ld_c_d}, {ld_c_e}, {ld_c_h}, {ld_c_l}, {ld_c_ahl}, {ld_c_a}, //40 -> 4f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //50 -> 5f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //60 -> 6f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_ahl_a}, {not_done}, {not_done}, {not_done}, {ld_a_e}, {not_done}, {not_done}, {not_done}, {not_done}, //70 -> 7f
	{add_a_b}, {add_a_c}, {add_a_d}, {add_a_e}, {add_a_h}, {add_a_l}, {add_a_ahl}, {add_a_a}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //80 -> 8f
	{sub_b}, {sub_c}, {sub_d}, {sub_e}, {sub_h}, {sub_l}, {sub_ahl}, {sub_a}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //90 -> 9f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {xor_a}, //a0 -> af
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //b0 -> bf
	{not_done}, {pop_bc}, {jp_nz_a16}, {jp_a16}, {not_done}, {push_bc}, {not_done}, {not_done}, {not_done}, {ret}, {not_done}, {op_cb}, {not_done}, {call_a16}, {not_done}, {not_done}, //c0 -> cf
	{not_done}, {pop_de}, {jp_nc_a16}, {empty}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {empty}, {not_done}, {empty}, {not_done}, {not_done}, //d0 -> df
	{ld_ad8_a}, {pop_hl}, {ld_ac_a}, {empty}, {empty}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {ld_ad16_a}, {empty}, {empty}, {empty}, {not_done}, {not_done}, //e0 -> ef
	{ld_a_ad8}, {pop_af}, {ld_a_ac}, {not_done}, {empty}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {empty}, {empty}, {cp_d8}, {not_done} //f0 -> ff
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
