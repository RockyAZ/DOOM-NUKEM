/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:30:39 by azaporoz          #+#    #+#             */
/*   Updated: 2018/07/23 17:30:40 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		main(int ac, char **av)
{
	t_main		*win;

	main_prepare(ac, av, &win);
	reader(win->data);
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	win->win = SDL_CreateWindow("WOLF_SDL", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	win->ren = SDL_CreateRenderer(win->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");

	texture_prepare(win);
	ray_player_prepare(win);
	// ray_casting(win);

win->screen = SDL_CreateTexture(win->ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);
SDL_SetTextureBlendMode(win->screen, SDL_BLENDMODE_BLEND);
	while (!win->quit)
	{
		win->fps = SDL_GetTicks();
		SDL_SetRenderDrawColor(win->ren, 0, 0, 0, 0);
		SDL_RenderClear(win->ren);
		event_callback(win);
		active_keys(win);
		ray_casting(win);
SDL_UpdateTexture(win->screen, NULL, win->buffer[0], WIDTH << 2);
			for(int j = 0; j < HEIGHT; j++)
				for(int h = 0; h < WIDTH; h++)
					win->buffer[j][h] = 0;
SDL_RenderCopy(win->ren, win->screen, NULL, NULL);
			printf("FPS:%d\n", 1000 /(SDL_GetTicks() - win->fps));
		SDL_RenderPresent(win->ren);
	}
	SDL_DestroyRenderer(win->ren);
	SDL_DestroyWindow(win->win);
	SDL_Quit();
	// SDL_FreeSurface(bmp);
}
