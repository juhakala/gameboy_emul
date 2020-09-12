#include "z80.h"
#include "struct.h"
#include "define.h"

static void printing(char *s1, char *s2, char *s3, int size, t_mem *mem)
{
    if (PRINT & 1)
        read_mem_bytes(mem, size);
    if (PRINT & 2)
        printf("	%s %s, %s", s1, s2, s3);
    printf("\n");
}

// 0x7c
int		bit_7h(t_mem *mem)
{
	if (PRINT)
        printing("BIT", "7", "H", 2, mem);
	if (((mem->reg->hl >> 15) & 1) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	SET_FLAG(5);
	return (2);
}
