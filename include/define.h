#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define ROM mem->rom
#define RAM mem->ram

#define CYCLE mem->cycle
#define PRINT 3 // 0 = no, 1 = hex, 2 = op_name, 3 = 1 + 2
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

#define REV_16(x) (unsigned short)(x >> 8 | ((x & 0xFF) << 8))

#endif
