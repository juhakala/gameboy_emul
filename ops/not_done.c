#include "z80.h"

int	ld_sp_d16(unsigned char *memory, t_mem *mem)
{
	if (PRINT)
		read_mem_bytes(memory, mem, 3);
	mem->reg->sp = memory[mem->reg->pc + 1];
	mem->reg->sp += memory[mem->reg->pc + 2] << 8;
	mem->cycle += 3;
	return (3);
}

int	max_not_done(unsigned char *memory, t_mem *mem)
{
	printf("	start_point 0x%05hx ", mem->reg->pc);
	return (-1);
}
int	not_done(unsigned char *memory, t_mem *mem)
{

	printf("not done yet : memory[PC](hex = %x, dec = %d), PC(short hex = %hx)\n	", memory[mem->reg->pc], memory[mem->reg->pc], mem->reg->pc);
	read_mem_bytes(memory, mem, 1);
	mem->not_done++;
//	exit(0);
//	printf("\n\n");
	return (-1);
}
