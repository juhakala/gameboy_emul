#include "z80.h"
#include "struct.h"
#include "define.h"

static void printing(char *s1, int size, t_mem *mem)
{
    if (PRINT & 1)
        read_mem_bytes(mem, size);
    if (PRINT & 2)
        printf("	XOR %s", s1);
    printf("\n");
}

int	xor_a(t_mem *mem)
{
	if (PRINT)
		printing("A", 1, mem);
	mem->reg->a ^= mem->reg->a; 
	mem->cycle += 4;
	SET_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	CLEAR_FLAG(4);
	return (1);
}
