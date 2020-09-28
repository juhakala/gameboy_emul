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
	
#endif
