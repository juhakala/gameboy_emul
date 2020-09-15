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

int		ld_ahl_a(t_mem *mem);
int		ld_a_e(t_mem *mem);
int		ld_ad8_a(t_mem *mem);
int		ld_ac_a(t_mem *mem);
int		ld_ad16_a(t_mem *mem);
int		ld_a_ad8(t_mem *mem);
int		ld_a_ac(t_mem *mem);

/*
** ops/xor.c
*/
int		xor_a(t_mem *mem);

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
int		bit_7h(t_mem *mem);

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

#endif
