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
int     rl_c(t_mem *mem)
{
	int carry;
	unsigned char c;

    if (PRINT)
        printing("RL", "C", 2, mem);
	c = mem->reg->bc & 0x00ff;
	carry = (c >> 7) & 1;
	c = (c << 1) + CHECK_FLAG(4);
	mem->reg->bc = (mem->reg->bc & 0xff00) + c;
	if ((mem->reg->bc & 0x00ff) == 0)
		SET_FLAG(7);
	else
		CLEAR_FLAG(7);
	CLEAR_FLAG(6);
	CLEAR_FLAG(5);
	if (carry == 1)
		SET_FLAG(4);
	else
		CLEAR_FLAG(4);
	mem->cycle += 8;
	return (2);
}
