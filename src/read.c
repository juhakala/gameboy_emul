#include "define.h"
#include "z80.h"
#include "struct.h"
#include "op.h"

t_op	g_op_tab[OP_TAB_SIZE] =
{
	{op_nop},	{ld_bc_d16},	{ld_abc_a},		{inc_bc},	{inc_b},	{dec_b},	{ld_b_d8},		{rlca},		{ld_a16_sp},	{add_hl_bc},	{ld_a_abc},		{dec_bc},	{inc_c},	{dec_c},	{ld_c_d8},		{rrca}, //0 -> f
	{stop},		{ld_de_d16},	{ld_ade_a},		{inc_de},	{inc_d},	{dec_d},	{ld_d_d8},		{rla},		{jr_s8},		{add_hl_de},	{ld_a_ade},		{dec_de},	{inc_e},	{dec_e},	{ld_e_d8},		{rra}, //10 -> 1f
	{jr_nz_s8},	{ld_hl_d16},	{ld_ahlp_a},	{inc_hl}, 	{inc_h},	{dec_h},	{ld_h_d8},		{not_done},	{jr_z_s8},		{add_hl_hl},	{ld_a_ahlp},	{dec_hl},	{inc_l},	{dec_l},	{ld_l_d8},		{cpf}, //20 -> 2f
	{jr_nc_s8},	{ld_sp_d16},	{ld_ahln_a}, 	{inc_sp}, 	{inc_ahl},	{dec_ahl},	{ld_ahl_d8},	{scf},		{jr_c_s8},		{add_hl_sp},	{ld_a_ahln},	{dec_sp},	{inc_a},	{dec_a},	{ld_a_d8},		{ccf}, //30 -> 3f
	{ld_b_b},	{ld_b_c},		{ld_b_d},		{ld_b_e},	{ld_b_h},	{ld_b_l},	{ld_b_ahl},		{ld_b_a},	{ld_c_b},		{ld_c_c},		{ld_c_d},		{ld_c_e},	{ld_c_h},	{ld_c_l},	{ld_c_ahl},		{ld_c_a}, //40 -> 4f
	{ld_d_b},	{ld_d_c},		{ld_d_d},		{ld_d_e},	{ld_d_h},	{ld_d_l},	{ld_d_ahl},		{ld_d_a},	{ld_e_b},		{ld_e_c},		{ld_e_d},		{ld_e_e},	{ld_e_h},	{ld_e_l},	{ld_e_ahl},		{ld_e_a}, //50 -> 5f
	{ld_h_b},	{ld_h_c},		{ld_h_d},		{ld_h_e},	{ld_h_h},	{ld_h_l},	{ld_h_ahl},		{ld_h_a},	{ld_h_b},		{ld_h_c},		{ld_h_d},		{ld_h_e},	{ld_h_h},	{ld_h_l},	{ld_h_ahl},		{ld_h_a}, //60 -> 6f
	{ld_ahl_b},	{ld_ahl_c},		{ld_ahl_d},		{ld_ahl_e},	{ld_ahl_h},	{ld_ahl_l},	{halt},			{ld_ahl_a}, {ld_a_b},		{ld_a_c},		{ld_a_d},		{ld_a_e},	{ld_a_h},	{ld_a_l},	{ld_a_ahl},		{ld_a_a}, //70 -> 7f
	{add_a_b},	{add_a_c},		{add_a_d},		{add_a_e},	{add_a_h},	{add_a_l},	{add_a_ahl},	{add_a_a},	{adc_a_b},		{adc_a_c},		{adc_a_d},		{adc_a_e},	{adc_a_h},	{adc_a_l},	{adc_a_ahl},	{adc_a_a}, //80 -> 8f
	{sub_b},	{sub_c},		{sub_d},		{sub_e},	{sub_h},	{sub_l},	{sub_ahl},		{sub_a},	{sdc_a_b},		{sdc_a_c},		{sdc_a_d},		{sdc_a_e},	{sdc_a_h},	{sdc_a_l},	{sdc_a_ahl},	{sdc_a_a}, //90 -> 9f
	{and_b},	{and_c},		{and_d},		{and_c},	{and_h},	{and_l},	{and_ahl},		{and_a},	{xor_b},		{xor_c},		{xor_d},		{xor_e},	{xor_h},	{xor_l},	{xor_ahl},		{xor_a}, //a0 -> af
	{or_b}, 	{or_c},			{or_d},			{or_e},		{or_h},		{or_l},		{or_ahl},		{or_a},		{cp_b},			{cp_c},			{cp_d},			{cp_e},		{cp_h},		{cp_l},		{cp_ahl},		{cp_a}, //b0 -> bf
	{ret_nz},	{pop_bc},		{jp_nz_a16},	{jp_a16},	{call_nz},	{push_bc},	{add_a_d8},		{rst_00},	{ret_z},		{ret},			{jp_z_a16},		{op_cb},	{call_z},	{call_a16},	{adc_a_d8},		{rst_08}, //c0 -> cf
	{ret_nc},	{pop_de},		{jp_nc_a16},	{empty},	{call_nc},	{push_de},	{sub_d8},		{rst_10},	{ret_c},		{reti},			{jp_c_a16},		{empty},	{call_c},	{empty},	{sdc_a_d8},		{rst_18}, //d0 -> df
	{ld_ad8_a},	{pop_hl},		{ld_ac_a},		{empty},	{empty},	{push_hl},	{and_d8},		{rst_20},	{add_sp_s8},	{jp_ahl},		{ld_ad16_a},	{empty},	{empty},	{empty},	{xor_d8},		{rst_28}, //e0 -> ef
	{ld_a_ad8},	{pop_af},		{ld_a_ac},		{di},		{empty},	{push_af},	{or_d8},		{rst_30},	{ld_hl_sp_s8},	{ld_sp_hl},		{ld_a_ad16},	{ime},		{empty},	{empty},	{cp_d8},		{rst_38} //f0 -> ff
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
	{res_0_b}, {res_0_c}, {res_0_d}, {res_0_e}, {res_0_h}, {res_0_l}, {res_0_ahl}, {res_0_a}, {res_1_b}, {res_1_c}, {res_1_d}, {res_1_e}, {res_1_h}, {res_1_l}, {res_1_ahl}, {res_1_a}, //80 -> 8f
	{res_2_b}, {res_2_c}, {res_2_d}, {res_2_e}, {res_2_h}, {res_2_l}, {res_2_ahl}, {res_2_a}, {res_3_b}, {res_3_c}, {res_3_d}, {res_3_e}, {res_3_h}, {res_3_l}, {res_3_ahl}, {res_3_a}, //90 -> 9f
	{res_4_b}, {res_4_c}, {res_4_d}, {res_4_e}, {res_4_h}, {res_4_l}, {res_4_ahl}, {res_4_a}, {res_5_b}, {res_5_c}, {res_5_d}, {res_5_e}, {res_5_h}, {res_5_l}, {res_5_ahl}, {res_5_a}, //a0 -> af
	{res_6_b}, {res_6_c}, {res_6_d}, {res_6_e}, {res_6_h}, {res_6_l}, {res_6_ahl}, {res_6_a}, {res_7_b}, {res_7_c}, {res_7_d}, {res_7_e}, {res_7_h}, {res_7_l}, {res_7_ahl}, {res_7_a}, //b0 -> bf
	{set_0_b}, {set_0_c}, {set_0_d}, {set_0_e}, {set_0_h}, {set_0_l}, {set_0_ahl}, {set_0_a}, {set_1_b}, {set_1_c}, {set_1_d}, {set_1_e}, {set_1_h}, {set_1_l}, {set_1_ahl}, {set_1_a}, //c0 -> cf
	{set_2_b}, {set_2_c}, {set_2_d}, {set_2_e}, {set_2_h}, {set_2_l}, {set_2_ahl}, {set_2_a}, {set_3_b}, {set_3_c}, {set_3_d}, {set_3_e}, {set_3_h}, {set_3_l}, {set_3_ahl}, {set_3_a}, //d0 -> df
	{set_4_b}, {set_4_c}, {set_4_d}, {set_4_e}, {set_4_h}, {set_4_l}, {set_4_ahl}, {set_4_a}, {set_5_b}, {set_5_c}, {set_5_d}, {set_5_e}, {set_5_h}, {set_5_l}, {set_5_ahl}, {set_5_a}, //e0 -> ef
	{set_6_b}, {set_6_c}, {set_6_d}, {set_6_e}, {set_6_h}, {set_6_l}, {set_6_ahl}, {set_6_a}, {set_7_b}, {set_7_c}, {set_7_d}, {set_7_e}, {set_7_h}, {set_7_l}, {set_7_ahl}, {set_7_a}, //f0 -> ff

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

	mem->last_cycle = mem->cycle;
	size = g_op_tab[read(mem->reg->pc, mem)].f(mem);
	mem->last_cycle = mem->cycle - mem->last_cycle;
/*	if (mem->reg->pc == 0x00fe)
	{
		printf("%d, %d\n", mem->reg->a, *mem->io_reg->ff50);
		exit(0);
		}*/
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
