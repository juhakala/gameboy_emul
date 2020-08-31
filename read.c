#include "define.h"
//#include "struct.h"
#include "z80.h"
#include "op.h"

t_op	g_op_tab[OP_TAB_SIZE] =
{
	{op_nop}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //0 -> f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //10 -> 1f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //20 -> 2f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //30 -> 3f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //40 -> 4f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //50 -> 5f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //60 -> 6f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //70 -> 7f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //80 -> 8f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //90 -> 9f
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //a0 -> af
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //b0 -> bf
	{not_done}, {not_done}, {not_done}, {op_jp_nn}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //c0 -> cf
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //d0 -> df
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, //e0 -> ef
	{not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {not_done}, {op_cp_n}, {not_done}, //f0 -> ff
	{max_not_done}
};

int	read_op_byte(t_mem *mem)
{
	int size = -1;

//	if (RAM[PC] < OP_TAB_SIZE)
//	{
//	printf("size = %d\n", size);
	size = g_op_tab[RAM[PC]].f(mem);

//	}
//	printf("RAM[PC] = %d'", RAM[PC]);
	return (size);
}

void read_mem_bytes(t_mem *mem, int size)
{
	int i = 0;

	printf("[%u] (%05hx -> %05hx): ", CYCLE, PC, (unsigned short)(PC + size));
	while (i < size)
	{
		printf("%02hhx ", *(PCR + i++));
	}
	printf("\n");
}
