#include "z80.h"
#include "define.h"
#include "op.h"
#include "struct.h"

void debug_print(t_mem *mem)
{
	printf("op in pc = %02x\n", read(PC, mem));
	printf("re pc = %04hx\n", PC);
	printf("re sp = %04hx\n", R_SP);
	printf("reg A = %02hhx\n", R_A);
	printf("reg F = %02hhx\n", R_F);
	printf("reg B = %02x\n", (R_BC >> 8) & 0xff);
	printf("reg C = %02x\n", R_BC & 0xff);
	printf("reg D = %02x\n", (R_DE >> 8) & 0xff);
	printf("reg E = %02x\n", R_DE & 0xff);
	printf("reg H = %02x\n", (R_HL >> 8) & 0xff);
	printf("reg L = %02x\n", R_HL & 0xff);
}

void debug_check(t_mem *mem)
{
	static int addr = 0x100;
	static char choose[5] = "addr";

	if (!strcmp(choose, "step"))
		addr--;
	if ((addr < 1 && !strcmp(choose, "step")) || (mem->reg->pc == addr && !strcmp(choose, "addr")))
	{
		debug_print(mem);
		scanf("%s", choose);
		if (!strcmp(choose, "addr"))
			scanf("%x", &addr);
		else
			scanf("%d", &addr);
		printf("%s\n", choose);
	}
}

void debug_ff_regs(t_mem *mem)
{
	printf("0x%04x:   ", 0xff00);
	for (int i = 0; i < 0x50; i++)
	{
		printf("%02x ", mem->rest_ram[i + 0x1f00]);
		if ((i + 1) % 4 == 0)
			printf("  ");
		if ((i + 1) % 8 == 0)
			printf("\n0x%04x:   ", 0xff01 + i);
	}
	
}
	

void debug_main(t_mem *mem)
{
//	debug_check(mem);
//	debug_ff_regs(mem);
}
