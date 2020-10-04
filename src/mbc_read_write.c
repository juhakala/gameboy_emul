#include "z80.h"

void	write_ff(unsigned short addr, unsigned char content, t_mem *mem)
{
	if (addr == 0)
		R_P1 = (content & 0x30);
	else if (addr == 1)
		R_SB = content;
	else if (addr == 2)
		R_SC = content;
	else if (addr == 4)
		R_DIV = 0;
	else if (addr == 5)
		R_TIMA = content;
	else if (addr == 6)
		R_TMA = content;
	else if (addr == 7)
	{
		R_TAC = content;
		mem->timer->tac_enable = (R_TAC & 4);
		mem->timer->tac_rate = (R_TAC & 3);
	}
	else if (addr == 0xf)
		R_IF = content;
	else if (addr == 0x10)
		R_NR10 = content;	
	else if (addr == 0x11)
		R_NR11 = content;
	else if (addr == 0x12)
		R_NR12 = content;
	else if (addr == 0x13)
		R_NR13 = content;
	else if (addr == 0x14)
		R_NR14 = content;
	else if (addr == 0x16)
		R_NR21 = content;
	else if (addr == 0x17)
		R_NR22 = content;
	else if (addr == 0x19)
		R_NR24 = content;
	else if (addr == 0x1a)
		R_NR30 = content;
	else if (addr == 0x1b)
		R_NR31 = content;
	else if (addr == 0x1c)
		R_NR32 = content;
	else if (addr == 0x1e)
		R_NR33 = content;
	else if (addr == 0x20)
		R_NR41 = content;
	else if (addr == 0x21)
		R_NR42 = content;
	else if (addr == 0x22)
		R_NR43 = content;
	else if (addr == 0x23)
		R_NR44 = content;
	else if (addr == 0x24)
		R_NR50 = content;
	else if (addr == 0x25)
		R_NR51 = content;
	else if (addr == 0x26)
		R_NR52 = content;
	else if (addr == 0x40)
		R_LCDC = content;
	else if (addr == 0x41)
		R_STAT = content;
	else if (addr == 0x42)
		R_SCY = content;
	else if (addr == 0x43)
		R_SCX = content;
	else if (addr == 0x44)
		R_LY = content;
	else if (addr == 0x45)
		R_LYC = content;
	else if (addr == 0x46)
	{
		R_DMA = (content % 0xf1);
		for (unsigned char i = 0; i < 0xa0; i++)
			mem->rest_ram[i + 0xe00] = read((R_DMA << 8) + i, mem);
	}
	else if (addr == 0x47)
		R_BGP = content;
	else if (addr == 0x48)
		R_OBP0 = content;
	else if (addr == 0x49)
		R_OBP1 = content;
	else if (addr == 0x4a)
		R_WY = content;
	else if (addr == 0x4b)
		R_WX = content;
	else if (addr == 0x50)
		BOOT = content;
}

void	write1(unsigned short addr, unsigned char content, t_mem *mem)
{
	if (addr >= 0 && addr <= 0x1fff)
		mem->memory->cram_enable = ((content & 0x0f) == 0x0a);
	else if (addr >= 0x2000 && addr <= 0x3fff)
	{
		mem->memory->rom_bank = (content & 31) + (mem->memory->rom_bank & 96);
		if (mem->memory->rom_bank == 0)
			mem->memory->rom_bank = 1;
	}
	else if (addr >= 0x4000 && addr <= 0x5fff)
	{
		if (mem->memory->cram_enable)
			mem->memory->cram_bank = (content & 3);
		else
			mem->memory->rom_bank = ((content & 3) << 5) + (mem->memory->rom_bank & 31);
	}
	else if (addr >= 0x6000 && addr <= 0x7fff)
		mem->memory->cram_mode = (content & 0xf);
	else if (addr >= 0x8000 && addr <= 0x9fff)
		mem->vram[addr - 0x8000] = content;
	else if (addr >= 0xa000 && addr <= 0xbfff)
		mem->ram[addr - 0xa000 + (mem->memory->cram_bank * 0x2000)] = content;
	else if (addr >= 0xc000 && addr <= 0xdfff)
		mem->wram[addr - 0xc000] = content;
	else if (addr >= 0xe000 && addr <= 0xfeff)
		mem->rest_ram[addr - 0xe000] = content;
	else if (addr >= 0xff00 && addr <= 0xff7f)
		write_ff(addr - 0xff00, content, mem);
	else if (addr >= 0xff80 && addr <= 0xfffe)
		mem->rest_ram[addr - 0xe000] = content;
	else if (addr == 0xffff)
		R_IE = content;
}

int		write(unsigned short addr, unsigned char content, t_mem *mem)
{
	if (addr == 0xff02 && content == 0x81)
		printf("%c", R_SB);
	if (mem->memory->mbc == 1)
		write1(addr, content, mem);
	write1(addr, content, mem);
	return (0);
}

unsigned char read_ff(unsigned short addr, t_mem *mem)
{
	if (addr == 0)
		return (0x0c | R_P1);
	else if (addr == 1)
		return (R_SB);
	else if (addr == 2)
		return (R_SC);
	else if (addr == 4)
		return (R_DIV);
	else if (addr == 5)
		return (R_TIMA);
	else if (addr == 6)
		return (R_TMA);
	else if (addr == 7)
		return (R_TAC);
	else if (addr == 0xf)
		return (R_IF);
	else if (addr == 0x10)
		return (R_NR10);
	else if (addr == 0x11)
		return (R_NR11);
	else if (addr == 0x12)
		return (R_NR12);
	else if (addr == 0x13)
		return (R_NR13);
	else if (addr == 0x14)
		return (R_NR14);
	else if (addr == 0x16)
		return (R_NR21);
	else if (addr == 0x17)
		return (R_NR22);
	else if (addr == 0x19)
		return (R_NR24);
	else if (addr == 0x1a)
		return (R_NR30);
	else if (addr == 0x1b)
		return (R_NR31);
	else if (addr == 0x1c)
		return (R_NR32);
	else if (addr == 0x1e)
		return (R_NR33);
	else if (addr == 0x20)
		return (R_NR41);
	else if (addr == 0x21)
		return (R_NR42);
	else if (addr == 0x22)
		return (R_NR43);
	else if (addr == 0x23)
		return (R_NR44);
	else if (addr == 0x24)
		return (R_NR50);
	else if (addr == 0x25)
		return (R_NR51);
	else if (addr == 0x26)
		return (R_NR52);
	else if (addr == 0x40)
		return (R_LCDC);
	else if (addr == 0x41)
		return ((R_STAT | 0xf8) | (R_LCDC & 0x80) ? mem->memory->lcd_mode : 1);
	else if (addr == 0x42)
		return (R_SCY);
	else if (addr == 0x43)
		return (R_SCX);
	else if (addr == 0x44)
		return (R_LY);
	else if (addr == 0x45)
		return (R_LYC);
	else if (addr == 0x46)
		return (R_DMA);
	else if (addr == 0x47)
		return (R_BGP);
	else if (addr == 0x48)
		return (R_OBP0);
	else if (addr == 0x49)
		return (R_OBP1);
	else if (addr == 0x4a)
		return (R_WY);
	else if (addr == 0x4b)
		return (R_WX);
	else if (addr == 0x50)
		return (BOOT);
	return (0);
}

unsigned char read1(unsigned short addr, t_mem *mem)
{
	if (BOOT == 0 && addr >= 0 && addr <= 0xff)
		return (mem->boot[addr]);
	else if (addr >= 0 && addr <= 0x3fff)
		return (mem->rom[addr]);
	else if (addr >= 0x4000 && addr <= 0x7fff)
		return (mem->rom[addr + ((mem->memory->rom_bank & 0x1f) - 1) * 0x4000]);
	else if (addr >= 0x8000 && addr <= 0x9fff)
		return (mem->vram[addr - 0x8000]);
	else if (addr >= 0xa000 && addr <= 0xbfff)
		return (mem->ram[addr - 0xa000]);
	else if (addr >= 0xc000 && addr <= 0xdfff)
		return (mem->wram[addr - 0xc000]);
	else if (addr >= 0xe000 && addr <= 0xfeff)
		return (mem->rest_ram[addr - 0xe000]);
	else if (addr >= 0xff00 && addr <= 0xff7f)
		return (read_ff(addr - 0xff00, mem));
	else if (addr >= 0xff80 && addr <= 0xfffe)
		return (mem->rest_ram[addr - 0xe000]);
	else if (addr == 0xffff)
		return (R_IE);
	return (0);
}

unsigned char	read(unsigned short addr, t_mem *mem)
{
	if (mem->memory->mbc == 1)
		return (read1(addr, mem));
	return (read1(addr, mem));
	return (0);
}
