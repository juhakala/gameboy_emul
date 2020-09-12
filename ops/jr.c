#include "z80.h"
#include "struct.h"
#include "define.h"

static void printing(char *s1, char *s2, int size, int yes,t_mem *mem)
{
	if (PRINT & 1)
		read_mem_bytes(mem, size);
	if (PRINT & 2)
		printf("	JR %s, %s	|	%s", s1, s2, yes == 1 ? "YES" : "NO");
	printf("\n");
}

// 0x20
int	jr_nz_s8(t_mem *mem)
{
	if (PRINT)
		printing("NZ", "s8", 2, CHECK_FLAG(7) == 0 ? 1 : 0, mem);
	if (CHECK_FLAG(7) == 0)
		mem->reg->pc += (char)read(mem->reg->pc + 1, mem);
	mem->cycle += 8;
	return (2);
}
