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

// 0xc5
int		push_bc(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("PUSH", "BC", 1, mem);
	write(--mem->reg->sp, (mem->reg->bc >> 8) & 0xff, mem);
	write(--mem->reg->sp, mem->reg->bc & 0xff, mem);
	mem->cycle += 16;
	return (1);
}

// 0xc1
int		pop_bc(t_mem *mem)
{
	unsigned short val;
	if (PRINT)
		printing("POP", "BC", 1, mem);
	mem->reg->bc = read(mem->reg->sp++, mem);
	mem->reg->bc += read(mem->reg->sp++, mem) << 8;
	mem->cycle += 12;
	return (1);
}

// 0xc9
int		ret(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("RET", "", 1, mem);
	mem->reg->pc = read(mem->reg->sp++, mem);
	mem->reg->pc += read(mem->reg->sp++, mem) << 8;
	return (0);
}

// 0xcd
int		call_a16(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("CALL", "a16", 3, mem);
	write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
	write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
	val = read(mem->reg->pc + 1, mem);
	val += read(mem->reg->pc + 2, mem) << 8;
	mem->reg->pc = val;
	mem->cycle += 12;
	return (0);
}
