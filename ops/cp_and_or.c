#include "z80.h"
#include "struct.h"
#include "define.h"

static void printing(char *s1, char *s2, int size, t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, size);
	if (PRINT & 2)
		printf("	%s %s", s1, s2);
	printf("\n");
}

// 0xfe
int     cp_d8(t_mem *mem)
{
	char val;
	if (PRINT)
		printing("CP", "d8", 2, mem);
	if ((val = mem->reg->a - read(mem->reg->pc + 1, mem)) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	SET_FLAG(6);
	if ((mem->reg->a ^ read(mem->reg->pc + 1, mem) ^ val) & 0x10)
		SET_FLAG(5);
	else
		CLEAR_FLAG(5);
	if (val & 0xff00)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->cycle += 8;
	return (2);
}
