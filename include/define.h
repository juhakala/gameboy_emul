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

#define R_P1 mem->rest_ram[0 + 0x1f00]
#define R_SB mem->rest_ram[1 + 0x1f00]
#define R_SC mem->rest_ram[2 + 0x1f00]
#define R_DIV mem->rest_ram[4 + 0x1f00]
#define R_TIMA mem->rest_ram[5 + 0x1f00]
#define R_TMA mem->rest_ram[6 + 0x1f00]
#define R_TAC mem->rest_ram[7 + 0x1f00]
#define R_IF mem->rest_ram[0xf + 0x1f00]
#define R_NR10 mem->rest_ram[0x10 + 0x1f00]
#define R_NR11 mem->rest_ram[0x11 + 0x1f00]
#define R_NR12 mem->rest_ram[0x12 + 0x1f00]
#define R_NR13 mem->rest_ram[0x13 + 0x1f00]
#define R_NR14 mem->rest_ram[0x14 + 0x1f00]
#define R_NR21 mem->rest_ram[0x16 + 0x1f00]
#define R_NR22 mem->rest_ram[0x17 + 0x1f00]
#define R_NR23 mem->rest_ram[0x18 + 0x1f00]
#define R_NR24 mem->rest_ram[0x19 + 0x1f00]
#define R_NR30 mem->rest_ram[0x1a + 0x1f00]
#define R_NR31 mem->rest_ram[0x1b + 0x1f00]
#define R_NR32 mem->rest_ram[0x1c + 0x1f00]
#define R_NR33 mem->rest_ram[0x1d + 0x1f00]
#define R_NR34 mem->rest_ram[0x1e + 0x1f00]
#define R_NR41 mem->rest_ram[0x20 + 0x1f00]
#define R_NR42 mem->rest_ram[0x21 + 0x1f00]
#define R_NR43 mem->rest_ram[0x22 + 0x1f00]
#define R_NR44 mem->rest_ram[0x23 + 0x1f00]
#define R_NR50 mem->rest_ram[0x24 + 0x1f00]
#define R_NR51 mem->rest_ram[0x25 + 0x1f00]
#define R_NR52 mem->rest_ram[0x26 + 0x1f00]
#define R_LCDC mem->rest_ram[0x40 + 0x1f00]
#define R_STAT mem->rest_ram[0x41 + 0x1f00]
#define R_SCY mem->rest_ram[0x42 + 0x1f00]
#define R_SCX mem->rest_ram[0x43 + 0x1f00]
#define R_LY mem->rest_ram[0x44 + 0x1f00]
#define R_LYC mem->rest_ram[0x45 + 0x1f00]
#define R_DMA mem->rest_ram[0x46 + 0x1f00]
#define R_BGP mem->rest_ram[0x47 + 0x1f00]
#define R_OBP0 mem->rest_ram[0x48 + 0x1f00]
#define R_OBP1 mem->rest_ram[0x49 + 0x1f00]
#define R_WY mem->rest_ram[0x4a + 0x1f00]
#define R_WX mem->rest_ram[0x4b + 0x1f00]
#define R_IE mem->rest_ram[0xff + 0x1f00]

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
