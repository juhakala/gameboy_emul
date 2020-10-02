#include "z80.h"

void    debug_print(t_mem *mem);

int		write(unsigned short addr, unsigned char content, t_mem *mem)
{
	if (addr == 0xff02 && content == 0x81)
		printf("%c", *mem->io_reg->ff01);
	if (addr >= 0x0 && addr <= 0x1fff)
	{
		if (content == 0x0a)
			mem->memory->ram_enable = 1;
		else
			mem->memory->ram_enable = 0;
	}
	else if (addr >= 0x2000 && addr <= 0x3fff)
	{
		if (mem->memory->mbc == 1)
		{
			mem->memory->rom_bank = (content & 0x1f) | (mem->memory->rom_bank & 0x60);
			if ((mem->memory->rom_bank & 0x1f) == 0)
				mem->memory->rom_bank = 1;
		}
		else if (mem->memory->mbc == 3)
		{
			mem->memory->rom_bank = content & 0x7f;
			if (mem->memory->rom_bank == 0)
				mem->memory->rom_bank = 1;
		}
	}
	else if (addr >= 0x4000 && addr <= 0x5fff)
	{
		if (mem->memory->mbc == 1)
		{
			mem->memory->ram_bank = (content & 3);
			mem->memory->rom_bank = ((content & 3) << 5) | (mem->memory->rom_bank & 0x1f);
			mem->memory->rom_bank = mem->memory->rom_bank % mem->memory->rom_banks;
		}
		else if  (mem->memory->mbc == 3)
		{
			mem->memory->ram_bank = content;
		}
	}
	else if (addr >= 0x6000 && addr <= 0x7fff)
	{
		if (content == 0x00)
			mem->memory->rom_ram_mode = 0;
		else if (content == 0x01)
			mem->memory->rom_ram_mode = 1;
	}
	else if (addr >= 0x8000 && addr <= 0x9fff)
		mem->vram[addr - 0x8000] = content;
	else if (addr >= 0xa000 && addr <= 0xbfff)
	{
		if (mem->memory->ram_enable == 1 && mem->memory->ram_bank < mem->memory->ram_banks)
			mem->ram[addr - 0xa000 + mem->memory->ram_bank * 0x2000] = content;
		else
			mem->ram[addr - 0xa000] = content;
	}
	else if (addr >= 0xc000 && addr <= 0xdfff)
		mem->wram[addr - 0xc000] = content;
	else if (addr >= 0xe000 && addr <= 0xffff)
	{
		if (addr == 0xff04)
			*mem->io_reg->ff04 = 0;
		else if (addr == 0xff07)
		{
			if ((*mem->io_reg->ff07 & 3) != (content & 3))
				set_timer_counter(mem);
			mem->rest_ram[addr - 0xe000] = content;
		}
		else if (addr == 0xff44)
			*mem->io_reg->ff44 = 0;
		else if (addr == 0xff46) //strt DMA transfer
		{
			unsigned short new_addr = content << 8; //source = content * 100
			for (int i = 0; i < 0xa0; i++)
				write(0xfe00 + i, read(new_addr + i, mem), mem); //sprite RAM 0xfe00 - 0xfe9f
		}
		else
			mem->rest_ram[addr - 0xe000] = content;
	}
	else
	{
		printf("mem->memory->mbc == %d\n", mem->memory->mbc);
		printf("only mbc 0, 1 or 3 now write addr = %04x, content = %02x\n", addr, content);
		printf("ram enable = %d\n", mem->memory->ram_enable);
		exit(0);
	}
	return (0);
}

unsigned char	read(unsigned short addr, t_mem *mem)
{
	if (addr >= 0x0000 && addr <= 0x3fff)
	{
		if (*mem->io_reg->ff50 == 0 && addr < 0x100)
			return (mem->boot[addr]);
		return (mem->rom[addr]);
	}
	else if (addr >= 0x4000 && addr <= 0x7fff)
	{
		if (mem->memory->mbc == 1)
			return (mem->rom[addr + ((mem->memory->rom_bank & 0x1f) - 1) * 0x4000]);
		return (mem->rom[addr + (mem->memory->rom_bank - 1) * 0x4000]);
	}
	else if (addr >= 0x8000 && addr <= 0x9fff) //video ram
		return (mem->vram[addr - 0x8000]);
	else if (addr >= 0xa000 && addr <= 0xbfff)
	{
		if (mem->memory->rom_ram_mode == 1 && mem->memory->ram_bank < mem->memory->ram_banks)
			return (mem->ram[addr - 0xa000 + mem->memory->ram_bank * 0x2000]);
		else
			return (mem->ram[addr - 0xa000]);
	}
	else if (addr >= 0xc000 && addr <= 0xdfff)
		return (mem->wram[addr - 0xc000]);
	else if (addr >= 0xe000 && addr <= 0xffff)
		return (mem->rest_ram[addr - 0xe000]);
	else
	{
		printf("mem->memory->mbc == %d\n", mem->memory->mbc);
		printf("only mbc 0, 1 or 3 now read, addr = %04x\n", addr);
		exit(0);
	}
	return (0);
}
