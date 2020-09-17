#include "z80.h"

// address of where we are writing,
// mbc 3
int		write3(unsigned short addr, unsigned char content, t_mem *mem)
{	
	if (addr >= 0x0000 && addr <= 0x1fff)
	{
		if (content == 0x0a)
			mem->memory->ram_enable = 1;
		else
			mem->memory->ram_enable = 0;
	}
	else if (addr >= 0x2000 && addr <= 0x3fff)
	{
		mem->memory->rom_bank = content & 127;
		if (mem->memory->rom_bank >= mem->memory->rom_banks)
		{
			if (mem->count != 1)
			{
				printf("rom bank too big\n");
				exit(0);
			}
			mem->memory->rom_bank = mem->memory->rom_banks - 1; //tmp for counting
		}
		if (mem->memory->rom_bank == 0)
			mem->memory->rom_bank = 1;
	}
	else if (addr >= 0x4000 && addr <= 0x5fff)
	{
		mem->memory->ram_bank = content;
		if (mem->memory->ram_bank >= mem->memory->ram_banks)
		{
			if (mem->count != 1)
			{
				printf("ram bank too big\n");
				exit(0);
			}
			mem->memory->ram_bank = mem->memory->ram_banks - 1; //tmp for counting
		}
	}
	else if (addr >= 0x6000 && addr <= 0x7fff)
	{
		if (content == 0x00)
			mem->memory->rom_ram_mode = 0;
		else if (content == 0x01)
			mem->memory->rom_ram_mode = 1;
		else if (mem->count != 1)
		{
			printf("we have a problem in write3 addr = '0x%04hx', content = '0x%02hhx'\n", addr, content);
			exit(0);
		}
	}
	else if (addr >= 0x8000 && addr <= 0x9fff)
		mem->vram[addr - 0x8000] = content;
	else if (addr >= 0xa000 && addr <= 0xbfff)
		mem->ram[addr - 0xa000 + mem->memory->ram_bank * 0x2000] = content;
	else if (addr >= 0xc000 && addr <= 0xdfff)
		mem->wram[addr - 0xc000] = content;
	else if (addr >= 0xe000 && addr <= 0xefff && mem->count != 1)
	{
		printf("echo ram write\n");
		exit(0);
	}
	else if (addr >= 0xfe00 && addr <= 0xfe9f)
		mem->oam[addr - 0xfe00] = content;
	else if (addr >= 0xff00 && addr <= 0xff7f)
	{
		if (addr == 0xff04)
			*mem->io_reg->ff04 = 0;
		else if (addr == 0xff07)
		{
			if ((*mem->io_reg->ff07 & 3) != (content & 3))
				set_timer_counter(mem);
			mem->i_o_registers[addr - 0xff00] = content;
		}
		else if (addr == 0xff44)
			*mem->io_reg->ff44 = 0;
		else
			mem->i_o_registers[addr - 0xff00] = content;
	}
	else if (addr >= 0xff80 && addr <= 0xfffe)
		mem->hram[addr - 0xff80] = content;
	else if (addr == 0xffff)
		mem->interrupts = content;
	else if (mem->count != 1)
	{
		printf("we have a problem in write3 addr = '0x%04hx', content = '0x%02hhx'\n", addr, content);
		exit(0);
	}
	return (0);
}

unsigned char	read3(unsigned short addr, t_mem *mem)
{
	if (addr >= 0x000 && addr <= 0x3fff)
	{
		if (*mem->io_reg->ff50 == 0 && addr < 0x100)
			return (mem->boot[addr]);
		return (mem->rom[addr]);
	}
	else if (addr >= 0x4000 && addr <= 0x7fff)
		return (mem->rom[addr + (mem->memory->rom_bank - 1) * 0x4000]);
	else if (addr >= 0xa000 && addr <= 0xbfff)
		return (mem->ram[addr - 0xa000 + mem->memory->ram_bank * 0x2000]);
	else if (addr >= 0xc000 && addr <= 0xdfff)
		return (mem->wram[addr - 0xc000]);
	else if (addr >= 0xe000 && addr <= 0xefff && mem->count != 1)
	{
		printf("echo ram read\n");
		exit(0);
	}
	else if (addr >= 0xfe00 && addr <= 0xfe9f)
		return (mem->oam[addr - 0xfe00]);
	else if (addr >= 0xff00 && addr <= 0xff7f)
	{
//		printf("addr = %04hx\n", addr);
		return (mem->i_o_registers[addr - 0xff00]); //right
	}
	else if (addr >= 0xff80 && addr <= 0xfffe)
		return (mem->hram[addr - 0xff80]);
	else if (addr == 0xffff)
		return (mem->interrupts);
	else if (mem->count != 1)
	{
		printf("we have a problem in read3 addr = '0x%04hx'\n", addr);
		exit(0);
	}
	return (0);
}

int		write(unsigned short addr, unsigned char content, t_mem *mem)
{
	if (mem->memory->mbc == 3)
		return (write3(addr, content, mem));
	else
	{
		printf("only mbc3 now\n");
		exit(0);
	}
	return (0);
}

unsigned char	read(unsigned short addr, t_mem *mem)
{
	if (addr == 0x0070)
		exit(0);
	if (mem->memory->mbc == 3)
	{
		return (read3(addr, mem));
	}
	else
	{
		printf("only mbc3 now\n");
		exit(0);
	}
	return (0);
}
