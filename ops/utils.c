#include "z80.h"

int		one_bit(char a, char b) // set if borrow
{
	return (a < b);
}

int		three_bit(char a,  char b, char c) // parity/overflow set
{
	int res;

	res = c == '-' ? a - b : a + b;
	return (res < -127 || res > 127 ? 4 : 0);
}

int		five_bit(char a, char b) // half borrow
{
	return ((a ^ b ^ (a - b)) & 16);
}

int		seven_bit(char a, char b) // if equal
{
	return (a == b ? 64 : 0);
}

int		eight_bit(char a, char b) // if minus
{
	return ((a - b) & 128);
}
