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

// 0xc0
int		ret_nz(t_mem *mem)
{
	if (PRINT)
		printing("RET", "NZ", 1, mem);
	mem->cycle += 8;
	if (CHECK_FLAG(7) == 0)
	{
		mem->reg->pc = read(mem->reg->sp++, mem);
		mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
		return (0);
	}
	return (1);
}

// 0xc1
int		pop_bc(t_mem *mem)
{
	if (PRINT)
		printing("POP", "BC", 1, mem);
	mem->reg->bc = read(mem->reg->sp++, mem);
	mem->reg->bc += read(mem->reg->sp++, mem) << 8;
	mem->cycle += 12;
	return (1);
}

// 0xc4
int		call_nz(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("CALL", "NZ", 3, mem);
	mem->cycle += 12;
	if (CHECK_FLAG(7) == 0)
	{
		write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
		write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
		val = read(mem->reg->pc + 1, mem);
		val += read(mem->reg->pc + 2, mem) << 8;
		mem->reg->pc = val;
		return (0);
	}
	return (3);
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

// 0xcc
int		call_z(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("CALL", "Z", 3, mem);
	mem->cycle += 12;
	if (CHECK_FLAG(7) == 1)
	{
		write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
		write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
		val = read(mem->reg->pc + 1, mem);
		val += read(mem->reg->pc + 2, mem) << 8;
		mem->reg->pc = val;
		return (0);
	}
	return (3);
}

// 0xc8
int		ret_z(t_mem *mem)
{
	if (PRINT)
		printing("RET", "Z", 1, mem);
	mem->cycle += 8;
	if (CHECK_FLAG(7) == 1)
	{
		mem->reg->pc = read(mem->reg->sp++, mem);
		mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
		return (0);
	}
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

// 0xd0
int		ret_nc(t_mem *mem)
{
	if (PRINT)
		printing("RET", "NC", 1, mem);
	mem->cycle += 8;
	if (CHECK_FLAG(4) == 0)
	{
		mem->reg->pc = read(mem->reg->sp++, mem);
		mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
		return (0);
	}
	return (1);
}

// 0xd1
int		pop_de(t_mem *mem)
{
	if (PRINT)
		printing("POP", "DE", 1, mem);
	mem->reg->de = read(mem->reg->sp++, mem);
	mem->reg->de += read(mem->reg->sp++, mem) << 8;
	mem->cycle += 12;
	return (1);
}

// 0xd4
int		call_nc(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("CALL", "NC", 3, mem);
	mem->cycle += 12;
	if (CHECK_FLAG(4) == 0)
	{
		write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
		write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
		val = read(mem->reg->pc + 1, mem);
		val += read(mem->reg->pc + 2, mem) << 8;
		mem->reg->pc = val;
		return (0);
	}
	return (3);
}

// 0xd5
int		push_de(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("PUSH", "DE", 1, mem);
	write(--mem->reg->sp, (mem->reg->de >> 8) & 0xff, mem);
	write(--mem->reg->sp, mem->reg->de & 0xff, mem);
	mem->cycle += 16;
	return (1);
}

// 0xd8
int		ret_c(t_mem *mem)
{
	if (PRINT)
		printing("RET", "C", 1, mem);
	mem->cycle += 8;
	if (CHECK_FLAG(4) == 1)
	{
		mem->reg->pc = read(mem->reg->sp++, mem);
		mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
		return (0);
	}
	return (1);
}

// 0xd9
int		reti(t_mem *mem)
{
	if (PRINT)
		printing("RETI", "", 1, mem);
	mem->reg->pc = read(mem->reg->sp++, mem);
	mem->reg->pc += (read(mem->reg->sp++, mem) << 8);
	mem->master_interrupt = 1;
	mem->cycle += 8;
	return (1);
}

// 0xdc
int		call_c(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("CALL", "C", 3, mem);
	mem->cycle += 12;
	if (CHECK_FLAG(4) == 1)
	{
		write(--mem->reg->sp, ((mem->reg->pc + 3) >> 8) & 0xff, mem);
		write(--mem->reg->sp, (mem->reg->pc + 3) & 0xff, mem);
		val = read(mem->reg->pc + 1, mem);
		val += read(mem->reg->pc + 2, mem) << 8;
		mem->reg->pc = val;
		return (0);
	}
	return (3);
}

// 0xe1
int		pop_hl(t_mem *mem)
{
	if (PRINT)
		printing("POP", "HL", 1, mem);
	mem->reg->hl = read(mem->reg->sp++, mem);
	mem->reg->hl += read(mem->reg->sp++, mem) << 8;
	mem->cycle += 12;
	return (1);
}

// 0xe5
int		push_hl(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("PUSH", "HL", 1, mem);
	write(--mem->reg->sp, (mem->reg->hl >> 8) & 0xff, mem);
	write(--mem->reg->sp, mem->reg->hl & 0xff, mem);
	mem->cycle += 16;
	return (1);
}

// 0xf1
int		pop_af(t_mem *mem)
{
	if (PRINT)
		printing("POP", "AF", 1, mem);
	mem->reg->f = read(mem->reg->sp++, mem);
	mem->reg->a = read(mem->reg->sp++, mem);
	mem->cycle += 12;
	return (1);
}

// 0xc5
int		push_af(t_mem *mem)
{
	unsigned short val;

	if (PRINT)
		printing("PUSH", "AF", 1, mem);
	write(--mem->reg->sp, mem->reg->a, mem);
	write(--mem->reg->sp, mem->reg->f, mem);
	mem->cycle += 16;
	return (1);
}
