#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define ROM mem->rom
#define RAM mem->ram

#define CYCLE mem->cycle
#define PRINT 0 // 0 = no, 1 = hex, 2 = op_name, 3 = 1 + 2
#define OP_TAB_SIZE 0x100 // max size of op list, change if you add op:s

#define PRI(x) print_f_flag(x, mem)
#define REGA PRI(mem->reg->a)
#define REGF PRI(mem->reg->f)
#define REGB PRI((mem->reg->bc >> 8) & 0xff)
#define REGC PRI((mem->reg->bc & 0xff)
#define REGD PRI((mem->reg->de >> 8) & 0xff)
#define REGE PRI(mem->reg->de& 0xff)
#define REGH PRI((mem->reg->hl >> 8) & 0xff)
#define REGL PRI(mem->reg->hl & 0xff)


#define SET_FLAG(n) (mem->reg->f |= (1 << n)) // set n:th bit
#define CLEAR_FLAG(n) (mem->reg->f &= ~(1 << n)) // clear n:th bit
#define CHECK_FLAG(n) ((mem->reg->f >> n) & 0x01) // check n:th bit

#define SET_BIT(n, x) (x |= (1 << n))
#define CLEAR_BIT(n, x) (x &= ~(1 << n))
#define CHECK_BIT(n, x) ((x >> n) & 0x01)

#define REV_16(x) (unsigned short)(x >> 8 | ((x & 0xFF) << 8))

#define WHITE 0xffffff00
#define LIGHT_GREY 0xcccccc00
#define DARK_GREY 0x77777700
#define BLACK 0x0

#define R_P1 mem->io_reg->r_p1
#define R_SB mem->io_reg->r_sb
#define R_SC mem->io_reg->r_sc
#define R_DIV mem->io_reg->r_div
#define R_TIMA mem->io_reg->r_tima
#define R_TMA mem->io_reg->r_tma
#define R_TAC mem->io_reg->r_tac
#define R_IF mem->io_reg->r_if
#define R_NR10 mem->io_reg->r_nr10
#define R_NR11 mem->io_reg->r_nr11
#define R_NR12 mem->io_reg->r_nr12
#define R_NR13 mem->io_reg->r_nr13
#define R_NR14 mem->io_reg->r_nr14
#define R_NR21 mem->io_reg->r_nr21
#define R_NR22 mem->io_reg->r_nr22
#define R_NR24 mem->io_reg->r_nr24
#define R_NR30 mem->io_reg->r_nr30
#define R_NR31 mem->io_reg->r_nr31
#define R_NR32 mem->io_reg->r_nr32
#define R_NR33 mem->io_reg->r_nr33
#define R_NR41 mem->io_reg->r_nr41
#define R_NR42 mem->io_reg->r_nr42
#define R_NR43 mem->io_reg->r_nr42
#define R_NR44 mem->io_reg->r_nr44
#define R_NR50 mem->io_reg->r_nr50
#define R_NR51 mem->io_reg->r_nr51
#define R_NR52 mem->io_reg->r_nr52
#define R_LCDC mem->io_reg->r_lcdc
#define R_STAT mem->io_reg->r_stat
#define R_SCY mem->io_reg->r_scy
#define R_SCX mem->io_reg->r_scx
#define R_LY mem->io_reg->r_ly
#define R_LYC mem->io_reg->r_lyc
#define R_DMA mem->io_reg->r_dma
#define R_BGP mem->io_reg->r_bgp
#define R_OBP0 mem->io_reg->r_obp0
#define R_OBP1 mem->io_reg->r_obp1
#define R_WY mem->io_reg->r_wy
#define R_WX mem->io_reg->r_wx
#define R_IE mem->io_reg->r_ie

#define BOOT mem->memory->boot
#define IME mem->ime
#define HALT mem->halt
#define PC mem->reg->pc

#define R_A mem->reg->a
#define R_F mem->reg->f
#define R_BC mem->reg->bc
#define R_DE mem->reg->de
#define R_HL mem->reg->hl
#define R_SP mem->reg->sp
	
#endif
