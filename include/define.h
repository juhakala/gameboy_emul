#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define RW_MEM_SIZE 26
#define MEM_SIZE 64000
#define START_POINT 0
#define RW mem->rw
#define RAM mem->ram

#define A &mem->rw[0]
#define F &mem->rw[1]
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
#define SP &mem->rw[14]

#define PCA &mem->rw[16] // address where PC is (in rw memory block [16 -17])

#define PC read_16bits(PCA) // read value from PC address

#define PCP(x) put_16bits((PC + x) % MEM_SIZE, PCA) // increment value of pc by x

#define PCR read_ram16bits(RAM, PCA) // address value of &mem->ram[0] + PC

#define Aalt &mem->rw[18]
#define Falt &mem->rw[19]
#define Balt &mem->rw[20]
#define Calt &mem->rw[21]
#define Dalt &mem->rw[22]
#define Ealt &mem->rw[23]
#define Halt &mem->rw[24]
#define Lalt &mem->rw[25]

#endif
