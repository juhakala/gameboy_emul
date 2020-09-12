#include "z80.h"
#include "struct.h"
#include "define.h"

static void printing(char *s1, char *s2, int size, t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, size);
	if (PRINT & 2)
		printf("	%s, %s", s1, s2);
	printf("\n");
}

// 0x0c
int		inc_c(t_mem *mem)
{
	char val = (mem->reg->bc & 0x00ff) + 1;

	if (PRINT)
		printing("INC", "C", 1, mem);
	mem->reg->bc = (mem->reg->bc & 0xff00) + val;
	return (1);
}
