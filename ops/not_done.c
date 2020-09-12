#include "z80.h"
#include "struct.h"
#include "define.h"


int	max_not_done(t_mem *mem)
{
	printf("	start_point 0x%05hx ", mem->reg->pc);
	return (-1);
}
int	not_done(t_mem *mem)
{

//	printf("not done yet : read(PC)(hex = %02x, dec = %d), PC(short hex = %02hx)\n	", read(mem->reg->pc, mem), read(mem->reg->pc, mem), mem->reg->pc);
//	read_mem_bytes(mem, 1);
	mem->not_done++;
//	exit(0);
//	printf("\n\n");
	return (-1);
}
