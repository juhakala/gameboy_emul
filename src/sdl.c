#include "z80.h"

void	quit_sdl(t_mem *mem)
{
	SDL_DestroyTexture(mem->sdl->text_lcd);
	SDL_DestroyRenderer(mem->sdl->ren);
	SDL_Quit();
	free(mem->sdl->pixel_lcd);
	mem->sdl->pixel_lcd = NULL;
}

void	render_sdl(t_mem *mem)
{
	SDL_Event event;

	//memset(mem->sdl->pixel_lcd, 125, 256 * 256 * sizeof(int));
	SDL_SetRenderDrawColor(mem->sdl->ren, 0, 0, 0, 0);
	SDL_RenderClear(mem->sdl->ren);
	SDL_UpdateTexture(mem->sdl->text_lcd, NULL, mem->sdl->pixel_lcd, 256 * sizeof(int));
	SDL_RenderCopy(mem->sdl->ren, mem->sdl->text_lcd, NULL, &mem->sdl->rect_lcd);
	SDL_RenderPresent(mem->sdl->ren);
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				quit_sdl(mem);
			else if (event.key.keysym.sym == SDLK_f)
				printf("FPS = %d\n", mem->fps);
		}
	}
}

int		sdl_init_error(const char *str)
{
	printf("%s\n", str);
	return (1);
}

int		init_sdl(t_mem *mem)
{
	mem->sdl->win = NULL;
	mem->sdl->ren = NULL;
	mem->sdl->text_lcd = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (sdl_init_error(SDL_GetError()));
	else if (!(mem->sdl->win = SDL_CreateWindow("Gameboy emulator",
												SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED,
												600, 600,
												SDL_WINDOW_RESIZABLE)))
		return (sdl_init_error(SDL_GetError()));
	else if (!(mem->sdl->ren = SDL_CreateRenderer(mem->sdl->win, -1, SDL_RENDERER_ACCELERATED)))
		return (sdl_init_error(SDL_GetError()));
	else if (!(mem->sdl->text_lcd = SDL_CreateTexture(mem->sdl->ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 256, 256)))
		return (sdl_init_error(SDL_GetError()));
	mem->sdl->pixel_lcd = (int*)malloc(sizeof(int) * (256 * 256));
	memset(mem->sdl->pixel_lcd, 125, 256 * 256 * sizeof(int));
	mem->sdl->rect_lcd.x = 172;
	mem->sdl->rect_lcd.y = 172;
	mem->sdl->rect_lcd.w = 256;
	mem->sdl->rect_lcd.h = 256;
	return (0);
}
