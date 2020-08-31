#include "z80.h"

int	op_jp_nn(t_mem *mem)
{
//	short val;	
	if (PRINT)
		read_mem_bytes(mem, 3);
	CYCLE += 3;
//	val = read_16bits(PCR + 1);//
//	printf("val = %hx\n", val);
//	printf("val = %hx\n", REV_16(val));
	PC_PUT(REV_16(read_16bits(PCR + 1)));
	return (0);
}
