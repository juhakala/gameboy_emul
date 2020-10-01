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
			printf("rom bank too big\n");
			exit(0);
		}
		if (mem->memory->rom_bank == 0)
			mem->memory->rom_bank = 1;
	}
	else if (addr >= 0x4000 && addr <= 0x5fff)
	{
		mem->memory->ram_bank = content;
		if (mem->memory->ram_bank >= mem->memory->ram_banks)
		{
			printf("addr = %04x, content = %02x\n", addr, content);
			printf("ram bank too big\n");
			exit(0);
		}
	}
	else if (addr >= 0x6000 && addr <= 0x7fff)
	{
		if (content == 0x00)
			mem->memory->rom_ram_mode = 0;
		else if (content == 0x01)
			mem->memory->rom_ram_mode = 1;
		else
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
	else
	{
		printf("we have a problem in write3 addr = '0x%04hx', content = '0x%02hhx'\n", addr, content);
		exit(0);
	}
	return (0);
}

unsigned char	read3(unsigned short addr, t_mem *mem)
{
	if (addr >= 0xa000 && addr <= 0xbfff)
		return (mem->ram[addr - 0xa000 + mem->memory->ram_bank * 0x2000]);
	else
	{
		printf("PC = %04x\n", mem->reg->pc);
		printf("addr = %04x\n", addr + (mem->memory->rom_bank - 1) * 0x4000);
		printf("DE = %04x\n", mem->reg->de);
		printf("we have a problem in read3 addr = '0x%04hx'\n", addr);
		exit(0);
	}
	return (0);
}

void    debug_print(t_mem *mem);

int		write(unsigned short addr, unsigned char content, t_mem *mem)
{
	if (addr >= 0xe000 && addr <= 0xffff)
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
		if (addr == 0xff02 && content == 0x81)
		{
			printf("%c", read(0xff01, mem));
		}
	}
	else if (addr >= 0x8000 && addr <= 0x9fff)
		mem->vram[addr - 0x8000] = content;
	else if (addr >= 0xc000 && addr <= 0xdfff)
		mem->wram[addr - 0xc000] = content;
	else if  (mem->memory->mbc == 3)
		return (write3(addr, content, mem));
	else
	{
		printf("mem->memory->mbc == %d\n", mem->memory->mbc);
		printf("only mbc 0, 1 or 3 now write addr = %04x, content = %02x\n", addr, content);
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
		return (mem->rom[addr + (mem->memory->rom_bank - 1) * 0x4000]);
	else if (addr >= 0x8000 && addr <= 0x9fff) //video ram
		return (mem->vram[addr - 0x8000]);
	else if (addr >= 0xc000 && addr <= 0xdfff)
		return (mem->wram[addr - 0xc000]);
	else if (addr >= 0xe000 && addr <= 0xffff)
		return (mem->rest_ram[addr - 0xe000]);
	else if  (mem->memory->mbc == 3)
	{
		return (read3(addr, mem));
	}
	else
	{
		printf("mem->memory->mbc == %d\n", mem->memory->mbc);
		printf("only mbc 0, 1 or 3 now read, addr = %04x\n", addr);
		exit(0);
	}
	return (0);
}
