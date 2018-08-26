/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:39:30 by azaporoz          #+#    #+#             */
/*   Updated: 2018/07/30 13:39:31 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wolf.h"

void	key_press_add(int key, t_main *win)
{
	if (key == SDLK_RIGHT)
		win->keys.right = 1;
	if (key == SDLK_LEFT)
		win->keys.left = 1;
	if (key == SDLK_UP)
		win->keys.up = 1;
	if (key == SDLK_DOWN)
		win->keys.down = 1;
	if (key == SDLK_w)
		win->keys.w = 1;
	if (key == SDLK_s)
		win->keys.s = 1;
	if (key == SDLK_a)
		win->keys.a = 1;
	if (key == SDLK_d)
		win->keys.d = 1;
	if (key == SDLK_LSHIFT)
		win->gg.speed = 10;
}

void	key_release_add(int key, t_main *win)
{
	if (key == SDLK_RIGHT)
		win->keys.right = 0;
	if (key == SDLK_LEFT)
		win->keys.left = 0;
	if (key == SDLK_UP)
		win->keys.up = 0;
	if (key == SDLK_DOWN)
		win->keys.down = 0;
	if (key == SDLK_w)
		win->keys.w = 0;
	if (key == SDLK_s)
		win->keys.s = 0;
	if (key == SDLK_a)
		win->keys.a = 0;
	if (key == SDLK_d)
		win->keys.d = 0;
	if (key == SDLK_LSHIFT)
		win->gg.speed = 5;
}

void	event_callback(t_main *win)
{
	while (SDL_PollEvent(&win->e))
	{
		if (win->e.type == SDL_MOUSEMOTION)
			mouse_pos(win);
		if (win->e.type == SDL_KEYDOWN)
		{
			if (win->e.key.keysym.sym == SDLK_SPACE)
			{
				if (SDL_GetRelativeMouseMode() == SDL_TRUE)
					SDL_SetRelativeMouseMode(SDL_FALSE);
				else
					SDL_SetRelativeMouseMode(SDL_TRUE);
			}
			if (win->e.key.keysym.sym  == SDLK_ESCAPE)
				win->quit = 1;
			key_press_add(win->e.key.keysym.sym, win);		
		}
		if (win->e.type == SDL_KEYUP)
			key_release_add(win->e.key.keysym.sym, win);
	}
}
