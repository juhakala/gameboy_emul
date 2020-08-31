#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define REV_16(x) (unsigned short)(x >> 8 | ((x & 0xFF) << 8))
#define RW_MEM_SIZE 26
//#define MEM_SIZE 64000
#define MEM_SIZE 65535
#define START_POINT 0x100
#define BUF_SIZE 8
#define RW mem->rw
#define RAM mem->ram
#define CYCLE mem->cycle
#define PRINT 1
#define OP_TAB_SIZE 0x101

#define A &mem->rw[0]
#define F &mem->rw[1]

#define SET_FLAG(n) (*F |= (1 << n))
#define CLEAR_FLAG(n) (*F &= ~(1 << n))
#define CHECK_FLAG(n) ((*F >> n) & 0x01)

#define SET_S_FLAG SET_FLAG(7)
#define CLEAR_S_FLAG CLEAR_FLAG(7)
#define CHECK_S_FLAG CHECK_FLAG(7)

#define SET_Z_FLAG SET_FLAG(6)
#define CLEAR_Z_FLAG CLEAR_FLAG(6)
#define CHECK_Z_FLAG CHECK_FLAG(6)

#define SET_H_FLAG SET_FLAG(4)
#define CLEAR_H_FLAG CLEAR_FLAG(4)
#define CHECK_H_FLAG CHECK_FLAG(4)

#define SET_PV_FLAG SET_FLAG(2)
#define CLEAR_PV_FLAG CLEAR_FLAG(2)
#define CHECK_PV_FLAG CHECK_FLAG(2)

#define SET_N_FLAG SET_FLAG(1)
#define CLEAR_N_FLAG CLEAR_FLAG(1)
#define CHECK_N_FLAG CHECK_FLAG(1)

#define SET_C_FLAG SET_FLAG(0)
#define CLEAR_C_FLAG CLEAR_FLAG(0)
#define CHECK_C_FLAG CHECK_FLAG(0)

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
#define SP_ADD(x) put_16bits(SP + x, SPA) // increment value of pc by x
#define SP_PUT(x) put_16bits(x, SPA) // increment value of pc by x
#define SPR read_ram16bits(RAM, SPA) // address value of &mem->ram[0] + SP

#define PCA &mem->rw[16] // address where PC is (in rw memory block [16 -17])
#define PC read_16bits(PCA) // read value from PC address
#define PC_ADD(x) put_16bits(PC + x, PCA) // increment value of pc by x
#define PC_PUT(x) put_16bits(x, PCA) // increment value of pc by x
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

#endif
