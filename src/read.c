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
	{rlc_b}, {rlc_c}, {rlc_d}, {rlc_e}, {rlc_h}, {rlc_l}, {rlc_ahl}, {rlc_a}, {rrc_b}, {rrc_c}, {rrc_d}, {rrc_e}, {rrc_h}, {rrc_l}, {rrc_ahl}, {rrc_a}, //0 -> f
	{rl_b}, {rl_c}, {rl_d}, {rl_e}, {rl_h}, {rl_l}, {rl_ahl}, {rl_a}, {rr_b}, {rr_c}, {rr_d}, {rr_e}, {rr_h}, {rr_l}, {rr_ahl}, {rr_a}, //10 -> 1f
	{sla_b}, {sla_c}, {sla_d}, {sla_e}, {sla_h}, {sla_l}, {sla_ahl}, {sla_a}, {sra_b}, {sra_c}, {sra_d}, {sra_e}, {sra_h}, {sra_l}, {sra_ahl}, {sra_a}, //20 -> 2f
	{swap_b}, {swap_c}, {swap_d}, {swap_e}, {swap_h}, {swap_l}, {swap_ahl}, {swap_a}, {srl_b}, {srl_c}, {srl_d}, {srl_e}, {srl_h}, {srl_l}, {srl_ahl}, {srl_a}, //30 -> 3f
	{bit_0_b}, {bit_0_c}, {bit_0_d}, {bit_0_e}, {bit_0_h}, {bit_0_l}, {bit_0_ahl}, {bit_0_a}, {bit_1_b}, {bit_1_c}, {bit_1_d}, {bit_1_e}, {bit_1_h}, {bit_1_l}, {bit_1_ahl}, {bit_1_a}, //40 -> 4f
	{bit_2_b}, {bit_2_c}, {bit_2_d}, {bit_2_e}, {bit_2_h}, {bit_2_l}, {bit_2_ahl}, {bit_2_a}, {bit_3_b}, {bit_3_c}, {bit_3_d}, {bit_3_e}, {bit_3_h}, {bit_3_l}, {bit_3_ahl}, {bit_3_a}, //50 -> 5f
	{bit_4_b}, {bit_4_c}, {bit_4_d}, {bit_4_e}, {bit_4_h}, {bit_4_l}, {bit_4_ahl}, {bit_4_a}, {bit_5_b}, {bit_5_c}, {bit_5_d}, {bit_5_e}, {bit_5_h}, {bit_5_l}, {bit_5_ahl}, {bit_5_a}, //60 -> 6f
	{bit_6_b}, {bit_6_c}, {bit_6_d}, {bit_6_e}, {bit_6_h}, {bit_6_l}, {bit_6_ahl}, {bit_6_a}, {bit_7_b}, {bit_7_c}, {bit_7_d}, {bit_7_e}, {bit_7_h}, {bit_7_l}, {bit_7_ahl}, {bit_7_a}, //70 -> 7f
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
