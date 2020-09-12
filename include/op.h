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
int		ld_c_d8(t_mem *mem);
int		ld_hl_d16(t_mem *mem);
int		ld_sp_d16(t_mem *mem);
int		ld_ahln_a(t_mem *mem);
int		ld_a_d8(t_mem *mem);
int		ld_ahl_a(t_mem *mem);
int		ld_ad8_a(t_mem *mem);
int		ld_ac_a(t_mem *mem);

/*
** ops/xor.c
*/
int		xor_a(t_mem *mem);

/*
** ops/jr.c
*/
int		jr_nz_s8(t_mem *mem);

int		op_cb(t_mem *mem); // redirect to bit operations

/*
** ops/bit_cb.c
*/
int		bit_7h(t_mem *mem);

#endif
