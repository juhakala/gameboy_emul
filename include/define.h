#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


#define RW_MEM_SIZE 26 // 208 bits
#define MEM_SIZE 65536 // max unsigned short
#define START_POINT 0x100 // 0x0100 is normally starting point for rom games
#define RW mem->rw
#define RAMI(x) mem->ram[(unsigned short)x]
#define RAM mem->ram
#define CYCLE mem->cycle
#define PRINT 1
#define OP_TAB_SIZE 0x101 // max size of op list, change if you add op:s

#define A &mem->rw[0]
#define F &mem->rw[1]

#define SET_FLAG(n) (*F |= (1 << n)) // set n:th bit
#define CLEAR_FLAG(n) (*F &= ~(1 << n)) // clear n:th bit
#define CHECK_FLAG(n) ((*F >> n) & 0x01) // check n:th bit

#define B &mem->rw[2]
#define C &mem->rw[3]
#define D &mem->rw[4]
#define E &mem->rw[5]
#define H &mem->rw[6]
#define L &mem->rw[7]

#define I &mem->rw[8]
#define R &mem->rw[9]
#define IX &mem->rw[10]
#define IY &mem->rw[12]

#define SPA &mem->rw[14]
#define SP read_16bits(SPA) // read value from SP address
#define SP_ADD(x) put_16bits(SP + x, SPA) // increment value of sp by x
#define SP_PUT(x) put_16bits(x, SPA) // put value x to sp
#define SPR read_ram16bits(RAM, SPA) // address value of &mem->ram[0] + SP

#define PCA &mem->rw[16] // address where PC is (in rw memory block [16 -17])
#define PC read_16bits(PCA) // read value from PC address
#define PC_ADD(x) put_16bits(PC + x, PCA) // increment value of pc by x
#define PC_PUT(x) put_16bits(x, PCA) // put value x to pc 
#define PCR read_ram16bits(RAM, PCA) // address value of &mem->ram[0] + PC
//#define PC_ADD(x) put_16bits((PC + x) % MEM_SIZE, PCA) // increment value of pc by x

#define Aalt &mem->rw[18]
#define Falt &mem->rw[19]
#define Balt &mem->rw[20]
#define Calt &mem->rw[21]
#define Dalt &mem->rw[22]
#define Ealt &mem->rw[23]
#define Halt &mem->rw[24]
#define Lalt &mem->rw[25]

#define REV_16(x) (unsigned short)(x >> 8 | ((x & 0xFF) << 8))
#define BUF_SIZE 8

#endif
