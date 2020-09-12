#include "z80.h"
#include "struct.h"
#include "define.h"

int	not_done(t_mem *mem)
{

//	printf("not done yet : read(PC)(hex = %02x, dec = %d), PC(short hex = %02hx)\n	", read(mem->reg->pc, mem), read(mem->reg->pc, mem), mem->reg->pc);
//	read_mem_bytes(mem, 1);
	mem->not_done++;
//	exit(0);
//	printf("\n\n");
	return (-1);
}
