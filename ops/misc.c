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

// 0x11
int		rla(t_mem *mem)
{
	int carry;

	if (PRINT)
		printing("RLA", "", 1, mem);
    carry = (mem->reg->a >> 7) & 1;
    mem->reg->a = (mem->reg->a << 1) + CHECK_FLAG(4);
	CLEAR_FLAG(7);
    CLEAR_FLAG(6);
    CLEAR_FLAG(5);
    if (carry == 1)
        SET_FLAG(4);
    else
        CLEAR_FLAG(4);
    mem->cycle += 4;
    return (1);
}
