#ifndef OP_H
#define OP_H

int		max_not_done(t_mem *mem);
int		not_done(t_mem *mem);




/*
** ops*.c
*/
int		op_nop(t_mem *mem); // 0x00

/*
** ops/ld.c
*/
int		ld_bc_d16(t_mem *mem);
int		ld_abc_a(t_mem *mem);
int		ld_b_d8(t_mem *mem);
int		ld_a_abc(t_mem *mem);
int		ld_c_d8(t_mem *mem);
int		ld_de_d16(t_mem *mem);
int		ld_ade_a(t_mem *mem);
int		ld_d_d8(t_mem *mem);
int		ld_a_ade(t_mem *mem);
int		ld_hl_d16(t_mem *mem);
int		ld_ahlp_a(t_mem *mem);
int		ld_l_d8(t_mem *mem);
int		ld_sp_d16(t_mem *mem);
int		ld_ahln_a(t_mem *mem);
int		ld_a_d8(t_mem *mem);
int		ld_c_a(t_mem *mem);
int		ld_ahl_a(t_mem *mem);
int		ld_a_e(t_mem *mem);
int		ld_ad8_a(t_mem *mem);
int		ld_ac_a(t_mem *mem);
int		ld_ad16_a(t_mem *mem);

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
** ops/inc_dec.c
*/
int		inc_bc(t_mem *mem);
int		dec_b(t_mem *mem);
int		inc_c(t_mem *mem);
int		dec_c(t_mem *mem);
int		inc_de(t_mem *mem);
int		inc_hl(t_mem *mem);
int		inc_sp(t_mem *mem);
int		dec_a(t_mem *mem);

/*
** ops/call_push_pop_ret.c
*/
int		push_bc(t_mem *mem);
int		pop_bc(t_mem *mem);
int		ret(t_mem *mem);
int		call_a16(t_mem *mem);

/*
** ops/cp_and_or.c
*/
int		cp_d8(t_mem *mem);

/*
** ops/misc.c
*/
int		rla(t_mem *mem);



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
int		rl_c(t_mem *mem);

#endif
