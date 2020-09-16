#ifndef OP_H
#define OP_H

int		max_not_done(t_mem *mem);
int		not_done(t_mem *mem);




/*
** ops*.c
*/
int		op_nop(t_mem *mem); // 0x00
int		empty(t_mem *mem);

/*
** ops/ld.c
*/
int		ld_bc_d16(t_mem *mem);
int		ld_abc_a(t_mem *mem);
int		ld_b_d8(t_mem *mem);
int		ld_a16_sp(t_mem *mem);
int		ld_a_abc(t_mem *mem);
int		ld_c_d8(t_mem *mem);
int		ld_de_d16(t_mem *mem);
int		ld_ade_a(t_mem *mem);
int		ld_d_d8(t_mem *mem);
int		ld_a_ade(t_mem *mem);
int		ld_e_d8(t_mem *mem);
int		ld_h_d8(t_mem *mem);
int		ld_hl_d16(t_mem *mem);
int		ld_ahlp_a(t_mem *mem);
int		ld_l_d8(t_mem *mem);
int		ld_sp_d16(t_mem *mem);
int		ld_ahln_a(t_mem *mem);
int		ld_a_d8(t_mem *mem);
int		ld_b_b(t_mem *mem);
int		ld_b_c(t_mem *mem);
int		ld_b_d(t_mem *mem);
int		ld_b_e(t_mem *mem);
int		ld_b_h(t_mem *mem);
int		ld_b_l(t_mem *mem);
int		ld_b_ahl(t_mem *mem);
int		ld_b_a(t_mem *mem);
int		ld_c_b(t_mem *mem);
int		ld_c_c(t_mem *mem);
int		ld_c_d(t_mem *mem);
int		ld_c_e(t_mem *mem);
int		ld_c_h(t_mem *mem);
int		ld_c_l(t_mem *mem);
int		ld_c_ahl(t_mem *mem);
int		ld_c_a(t_mem *mem);
int		ld_d_b(t_mem *mem);
int		ld_d_c(t_mem *mem);
int		ld_d_d(t_mem *mem);
int		ld_d_e(t_mem *mem);
int		ld_d_h(t_mem *mem);
int		ld_d_l(t_mem *mem);
int		ld_d_ahl(t_mem *mem);
int		ld_d_a(t_mem *mem);
int		ld_e_b(t_mem *mem);
int		ld_e_c(t_mem *mem);
int		ld_e_d(t_mem *mem);
int		ld_e_e(t_mem *mem);
int		ld_e_h(t_mem *mem);
int		ld_e_l(t_mem *mem);
int		ld_e_ahl(t_mem *mem);
int		ld_e_a(t_mem *mem);
int		ld_h_b(t_mem *mem);
int		ld_h_c(t_mem *mem);
int		ld_h_d(t_mem *mem);
int		ld_h_e(t_mem *mem);
int		ld_h_h(t_mem *mem);
int		ld_h_l(t_mem *mem);
int		ld_h_ahl(t_mem *mem);
int		ld_h_a(t_mem *mem);
int		ld_l_b(t_mem *mem);
int		ld_l_c(t_mem *mem);
int		ld_l_d(t_mem *mem);
int		ld_l_e(t_mem *mem);
int		ld_l_h(t_mem *mem);
int		ld_l_l(t_mem *mem);
int		ld_l_ahl(t_mem *mem);
int		ld_l_a(t_mem *mem);
int		ld_ahl_b(t_mem *mem);
int		ld_ahl_c(t_mem *mem);
int		ld_ahl_d(t_mem *mem);
int		ld_ahl_e(t_mem *mem);
int		ld_ahl_h(t_mem *mem);
int		ld_ahl_l(t_mem *mem);
int		ld_ahl_a(t_mem *mem);
int		ld_a_b(t_mem *mem);
int		ld_a_c(t_mem *mem);
int		ld_a_d(t_mem *mem);
int		ld_a_e(t_mem *mem);
int		ld_a_h(t_mem *mem);
int		ld_a_l(t_mem *mem);
int		ld_a_ahl(t_mem *mem);
int		ld_a_a(t_mem *mem);
int		ld_ad8_a(t_mem *mem);
int		ld_ac_a(t_mem *mem);
int		ld_ad16_a(t_mem *mem);
int		ld_a_ad8(t_mem *mem);
int		ld_a_ac(t_mem *mem);

/*
** ops/and_xor.c
*/
int		xor_b(t_mem *mem);
int		xor_c(t_mem *mem);
int		xor_d(t_mem *mem);
int		xor_e(t_mem *mem);
int		xor_h(t_mem *mem);
int		xor_l(t_mem *mem);
int		xor_ahl(t_mem *mem);
int		xor_a(t_mem *mem);
int		xor_d8(t_mem *mem);

/*
** ops/jr.c
*/
int		jr_s8(t_mem *mem);
int		jr_nz_s8(t_mem *mem);
int		jr_z_s8(t_mem *mem);
int		jr_nc_s8(t_mem *mem);
int		jr_c_s8(t_mem *mem);

/*
** ops/jr.c
*/
int		jp_nz_a16(t_mem *mem);
int		jp_a16(t_mem *mem);
int		jp_nc_a16(t_mem *mem);

/*
** ops/inc_dec.c
*/
int		inc_bc(t_mem *mem);
int		inc_b(t_mem *mem);
int		dec_b(t_mem *mem);
int		dec_bc(t_mem *mem);
int		inc_c(t_mem *mem);
int		dec_d(t_mem *mem);
int		dec_c(t_mem *mem);
int		inc_de(t_mem *mem);
int		inc_d(t_mem *mem);
int		dec_de(t_mem *mem);
int		inc_e(t_mem *mem);
int		inc_hl(t_mem *mem);
int		inc_h(t_mem *mem);
int		dec_h(t_mem *mem);
int		dec_hl(t_mem *mem);
int		inc_l(t_mem *mem);
int		inc_sp(t_mem *mem);
int		dec_sp(t_mem *mem);
int		dec_a(t_mem *mem);

/*
** ops/call_push_pop_ret.c
*/
int		push_bc(t_mem *mem);
int		pop_bc(t_mem *mem);
int		ret(t_mem *mem);
int		call_a16(t_mem *mem);
int		pop_de(t_mem *mem);
int		pop_hl(t_mem *mem);
int		pop_af(t_mem *mem);

/*
** ops/cp_and_or.c
*/
int		or_b(t_mem *mem);
int		or_c(t_mem *mem);
int		or_d(t_mem *mem);
int		or_e(t_mem *mem);
int		or_h(t_mem *mem);
int		or_l(t_mem *mem);
int		or_ahl(t_mem *mem);
int		or_a(t_mem *mem);
int		cp_b(t_mem *mem);
int		cp_c(t_mem *mem);
int		cp_d(t_mem *mem);
int		cp_e(t_mem *mem);
int		cp_h(t_mem *mem);
int		cp_l(t_mem *mem);
int		cp_ahl(t_mem *mem);
int		cp_a(t_mem *mem);
int		or_d8(t_mem *mem);
int		cp_d8(t_mem *mem);

/*
** ops/add_sub.c
*/
int		add_hl_bc(t_mem *mem);
int		add_hl_de(t_mem *mem);
int		add_hl_hl(t_mem *mem);
int		add_hl_sp(t_mem *mem);
int		add_a_b(t_mem *mem);
int		add_a_c(t_mem *mem);
int		add_a_d(t_mem *mem);
int		add_a_e(t_mem *mem);
int		add_a_h(t_mem *mem);
int		add_a_l(t_mem *mem);
int		add_a_ahl(t_mem *mem);
int		add_a_a(t_mem *mem);
int		sub_b(t_mem *mem);
int		sub_c(t_mem *mem);
int		sub_d(t_mem *mem);
int		sub_e(t_mem *mem);
int		sub_h(t_mem *mem);
int		sub_l(t_mem *mem);
int		sub_ahl(t_mem *mem);
int		sub_a(t_mem *mem);

/*
** ops/adc_sbc.c
*/
int		adc_a_b(t_mem *mem);
int		adc_a_c(t_mem *mem);
int		adc_a_d(t_mem *mem);
int		adc_a_e(t_mem *mem);
int		adc_a_h(t_mem *mem);
int		adc_a_l(t_mem *mem);
int		adc_a_ahl(t_mem *mem);
int		adc_a_a(t_mem *mem);
int		sdc_a_b(t_mem *mem);
int		sdc_a_c(t_mem *mem);
int		sdc_a_d(t_mem *mem);
int		sdc_a_e(t_mem *mem);
int		sdc_a_h(t_mem *mem);
int		sdc_a_l(t_mem *mem);
int		sdc_a_ahl(t_mem *mem);
int		sdc_a_a(t_mem *mem);
int		adc_a_d8(t_mem *mem);
int		sdc_a_d8(t_mem *mem);

/*
** ops/misc.c
*/
int		rlca(t_mem *mem);
int		rla(t_mem *mem);
int		scf(t_mem *mem);


//
int		op_cb(t_mem *mem); // redirect to bit operations
//

/*
** ops/bit_cb.c
*/
int		bit_0_b(t_mem *mem);
int		bit_0_c(t_mem *mem);
int		bit_0_d(t_mem *mem);
int		bit_0_e(t_mem *mem);
int		bit_0_h(t_mem *mem);
int		bit_0_l(t_mem *mem);
int		bit_0_ahl(t_mem *mem);
int		bit_0_a(t_mem *mem);
int		bit_1_b(t_mem *mem);
int		bit_1_c(t_mem *mem);
int		bit_1_d(t_mem *mem);
int		bit_1_e(t_mem *mem);
int		bit_1_h(t_mem *mem);
int		bit_1_l(t_mem *mem);
int		bit_1_ahl(t_mem *mem);
int		bit_1_a(t_mem *mem);
int		bit_2_b(t_mem *mem);
int		bit_2_c(t_mem *mem);
int		bit_2_d(t_mem *mem);
int		bit_2_e(t_mem *mem);
int		bit_2_h(t_mem *mem);
int		bit_2_l(t_mem *mem);
int		bit_2_ahl(t_mem *mem);
int		bit_2_a(t_mem *mem);
int		bit_3_b(t_mem *mem);
int		bit_3_c(t_mem *mem);
int		bit_3_d(t_mem *mem);
int		bit_3_e(t_mem *mem);
int		bit_3_h(t_mem *mem);
int		bit_3_l(t_mem *mem);
int		bit_3_ahl(t_mem *mem);
int		bit_3_a(t_mem *mem);
int		bit_4_b(t_mem *mem);
int		bit_4_c(t_mem *mem);
int		bit_4_d(t_mem *mem);
int		bit_4_e(t_mem *mem);
int		bit_4_h(t_mem *mem);
int		bit_4_l(t_mem *mem);
int		bit_4_ahl(t_mem *mem);
int		bit_4_a(t_mem *mem);
int		bit_5_b(t_mem *mem);
int		bit_5_c(t_mem *mem);
int		bit_5_d(t_mem *mem);
int		bit_5_e(t_mem *mem);
int		bit_5_h(t_mem *mem);
int		bit_5_l(t_mem *mem);
int		bit_5_ahl(t_mem *mem);
int		bit_5_a(t_mem *mem);
int		bit_6_b(t_mem *mem);
int		bit_6_c(t_mem *mem);
int		bit_6_d(t_mem *mem);
int		bit_6_e(t_mem *mem);
int		bit_6_h(t_mem *mem);
int		bit_6_l(t_mem *mem);
int		bit_6_ahl(t_mem *mem);
int		bit_6_a(t_mem *mem);
int		bit_7_b(t_mem *mem);
int		bit_7_c(t_mem *mem);
int		bit_7_d(t_mem *mem);
int		bit_7_e(t_mem *mem);
int		bit_7_h(t_mem *mem);
int		bit_7_l(t_mem *mem);
int		bit_7_ahl(t_mem *mem);
int		bit_7_a(t_mem *mem);


/*
** ops/rlc_rrc_cb.c
*/
int		rlc_b(t_mem *mem);
int		rlc_c(t_mem *mem);
int		rlc_d(t_mem *mem);
int		rlc_e(t_mem *mem);
int		rlc_h(t_mem *mem);
int		rlc_l(t_mem *mem);
int		rlc_ahl(t_mem *mem);
int		rlc_a(t_mem *mem);
int		rrc_b(t_mem *mem);
int		rrc_c(t_mem *mem);
int		rrc_d(t_mem *mem);
int		rrc_e(t_mem *mem);
int		rrc_h(t_mem *mem);
int		rrc_l(t_mem *mem);
int		rrc_ahl(t_mem *mem);
int		rrc_a(t_mem *mem);
int		rl_b(t_mem *mem);
int		rl_c(t_mem *mem);
int		rl_d(t_mem *mem);
int		rl_e(t_mem *mem);
int		rl_h(t_mem *mem);
int		rl_l(t_mem *mem);
int		rl_ahl(t_mem *mem);
int		rl_a(t_mem *mem);
int		rr_b(t_mem *mem);
int		rr_c(t_mem *mem);
int		rr_d(t_mem *mem);
int		rr_e(t_mem *mem);
int		rr_h(t_mem *mem);
int		rr_l(t_mem *mem);
int		rr_ahl(t_mem *mem);
int		rr_a(t_mem *mem);
int		sla_b(t_mem *mem);
int		sla_c(t_mem *mem);
int		sla_d(t_mem *mem);
int		sla_e(t_mem *mem);
int		sla_h(t_mem *mem);
int		sla_l(t_mem *mem);
int		sla_ahl(t_mem *mem);
int		sla_a(t_mem *mem);
int		sra_b(t_mem *mem);
int		sra_c(t_mem *mem);
int		sra_d(t_mem *mem);
int		sra_e(t_mem *mem);
int		sra_h(t_mem *mem);
int		sra_l(t_mem *mem);
int		sra_ahl(t_mem *mem);
int		sra_a(t_mem *mem);
int		swap_b(t_mem *mem);
int		swap_c(t_mem *mem);
int		swap_d(t_mem *mem);
int		swap_e(t_mem *mem);
int		swap_h(t_mem *mem);
int		swap_l(t_mem *mem);
int		swap_ahl(t_mem *mem);
int		swap_a(t_mem *mem);
int		srl_b(t_mem *mem);
int		srl_c(t_mem *mem);
int		srl_d(t_mem *mem);
int		srl_e(t_mem *mem);
int		srl_h(t_mem *mem);
int		srl_l(t_mem *mem);
int		srl_ahl(t_mem *mem);
int		srl_a(t_mem *mem);

/*
** ops/bit_cb.c
*/
int		res_0_b(t_mem *mem);
int		res_0_c(t_mem *mem);
int		res_0_d(t_mem *mem);
int		res_0_e(t_mem *mem);
int		res_0_h(t_mem *mem);
int		res_0_l(t_mem *mem);
int		res_0_ahl(t_mem *mem);
int		res_0_a(t_mem *mem);
int		res_1_b(t_mem *mem);
int		res_1_c(t_mem *mem);
int		res_1_d(t_mem *mem);
int		res_1_e(t_mem *mem);
int		res_1_h(t_mem *mem);
int		res_1_l(t_mem *mem);
int		res_1_ahl(t_mem *mem);
int		res_1_a(t_mem *mem);
int		res_2_b(t_mem *mem);
int		res_2_c(t_mem *mem);
int		res_2_d(t_mem *mem);
int		res_2_e(t_mem *mem);
int		res_2_h(t_mem *mem);
int		res_2_l(t_mem *mem);
int		res_2_ahl(t_mem *mem);
int		res_2_a(t_mem *mem);
int		res_3_b(t_mem *mem);
int		res_3_c(t_mem *mem);
int		res_3_d(t_mem *mem);
int		res_3_e(t_mem *mem);
int		res_3_h(t_mem *mem);
int		res_3_l(t_mem *mem);
int		res_3_ahl(t_mem *mem);
int		res_3_a(t_mem *mem);
int		res_4_b(t_mem *mem);
int		res_4_c(t_mem *mem);
int		res_4_d(t_mem *mem);
int		res_4_e(t_mem *mem);
int		res_4_h(t_mem *mem);
int		res_4_l(t_mem *mem);
int		res_4_ahl(t_mem *mem);
int		res_4_a(t_mem *mem);
int		res_5_b(t_mem *mem);
int		res_5_c(t_mem *mem);
int		res_5_d(t_mem *mem);
int		res_5_e(t_mem *mem);
int		res_5_h(t_mem *mem);
int		res_5_l(t_mem *mem);
int		res_5_ahl(t_mem *mem);
int		res_5_a(t_mem *mem);
int		res_6_b(t_mem *mem);
int		res_6_c(t_mem *mem);
int		res_6_d(t_mem *mem);
int		res_6_e(t_mem *mem);
int		res_6_h(t_mem *mem);
int		res_6_l(t_mem *mem);
int		res_6_ahl(t_mem *mem);
int		res_6_a(t_mem *mem);
int		res_7_b(t_mem *mem);
int		res_7_c(t_mem *mem);
int		res_7_d(t_mem *mem);
int		res_7_e(t_mem *mem);
int		res_7_h(t_mem *mem);
int		res_7_l(t_mem *mem);
int		res_7_ahl(t_mem *mem);
int		res_7_a(t_mem *mem);
int		set_0_b(t_mem *mem);
int		set_0_c(t_mem *mem);
int		set_0_d(t_mem *mem);
int		set_0_e(t_mem *mem);
int		set_0_h(t_mem *mem);
int		set_0_l(t_mem *mem);
int		set_0_ahl(t_mem *mem);
int		set_0_a(t_mem *mem);
int		set_1_b(t_mem *mem);
int		set_1_c(t_mem *mem);
int		set_1_d(t_mem *mem);
int		set_1_e(t_mem *mem);
int		set_1_h(t_mem *mem);
int		set_1_l(t_mem *mem);
int		set_1_ahl(t_mem *mem);
int		set_1_a(t_mem *mem);
int		set_2_b(t_mem *mem);
int		set_2_c(t_mem *mem);
int		set_2_d(t_mem *mem);
int		set_2_e(t_mem *mem);
int		set_2_h(t_mem *mem);
int		set_2_l(t_mem *mem);
int		set_2_ahl(t_mem *mem);
int		set_2_a(t_mem *mem);
int		set_3_b(t_mem *mem);
int		set_3_c(t_mem *mem);
int		set_3_d(t_mem *mem);
int		set_3_e(t_mem *mem);
int		set_3_h(t_mem *mem);
int		set_3_l(t_mem *mem);
int		set_3_ahl(t_mem *mem);
int		set_3_a(t_mem *mem);
int		set_4_b(t_mem *mem);
int		set_4_c(t_mem *mem);
int		set_4_d(t_mem *mem);
int		set_4_e(t_mem *mem);
int		set_4_h(t_mem *mem);
int		set_4_l(t_mem *mem);
int		set_4_ahl(t_mem *mem);
int		set_4_a(t_mem *mem);
int		set_5_b(t_mem *mem);
int		set_5_c(t_mem *mem);
int		set_5_d(t_mem *mem);
int		set_5_e(t_mem *mem);
int		set_5_h(t_mem *mem);
int		set_5_l(t_mem *mem);
int		set_5_ahl(t_mem *mem);
int		set_5_a(t_mem *mem);
int		set_6_b(t_mem *mem);
int		set_6_c(t_mem *mem);
int		set_6_d(t_mem *mem);
int		set_6_e(t_mem *mem);
int		set_6_h(t_mem *mem);
int		set_6_l(t_mem *mem);
int		set_6_ahl(t_mem *mem);
int		set_6_a(t_mem *mem);
int		set_7_b(t_mem *mem);
int		set_7_c(t_mem *mem);
int		set_7_d(t_mem *mem);
int		set_7_e(t_mem *mem);
int		set_7_h(t_mem *mem);
int		set_7_l(t_mem *mem);
int		set_7_ahl(t_mem *mem);
int		set_7_a(t_mem *mem);

#endif
