/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 15:29:42 by azaporoz          #+#    #+#             */
/*   Updated: 2018/07/31 15:29:43 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

unsigned int	get_pixel(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;

	pixels = (unsigned int*)surface->pixels;
	return (pixels[(y * surface->w) + x]);
}

void	draw_floor(int x, int y, t_main *win)
{
	float	dist;
	int		nx;
	int		ny;

	while (y < HEIGHT)
	{
		dist = (((float)win->gg.height / ((float)y - (float)CENTR_H - win->gg.up_down)) * win->gg.to_screen) / ft_cos(ft_abs(win->ray.angle - win->gg.angle));
		ny = (int)(win->gg.p_y - (dist * ft_sin(win->ray.angle))) % CUBE;
		nx = (int)(win->gg.p_x + (dist * ft_cos(win->ray.angle))) % CUBE;
		win->buffer[y][x] = get_pixel(win->img.tex[6], nx, ny);
		// win->buffer[HEIGHT - y][x] = get_pixel(win->img.tex[6], nx, ny);
// if (win->hy && y == HEIGHT - 3)
// printf("X:%d\nY:%d\n\nNX:%d\nNY:%d\n\n\n\n", x, y, nx, ny);
		y++;
	}
}

// unigned int a;

// r 255 & a;
// a >> 8;
// g (255) & a;
// a >> 8;
// 255 & a;

void	add_draw(t_main *win, int x, int y, int tex_x, int tex_y, int color)
{
	if (color == 5)
	{
		if (win->ray.angle >= 0 && win->ray.angle <= 180 && win->h_is)
			win->buffer[y][x] = get_pixel(win->img.tex[5], tex_x, tex_y);
		else if (win->ray.angle >= 90 && win->ray.angle <= 270 && win->v_is)
			win->buffer[y][x] = get_pixel(win->img.tex[6], tex_x, tex_y);
		else if (win->ray.angle >= 180 && win->ray.angle < 360 && win->h_is)
			win->buffer[y][x] = get_pixel(win->img.tex[7], tex_x, tex_y);
		else if ((win->ray.angle > 270 || win->ray.angle < 90) && win->v_is)
			win->buffer[y][x] = get_pixel(win->img.tex[8], tex_x, tex_y);
	}
	else
			win->buffer[y][x] = get_pixel(win->img.tex[color], tex_x, tex_y);
}

void	draw(int x, int y, t_main *win, int color)
{
	int		i;
	int		h;
	float	tex;
	float	tex_size;

	tex_size = (float)CUBE / (float)y;
	tex = tex_size;
	h = CENTR_H + (y >> 1) + win->gg.up_down;
	y = CENTR_H - (y >> 1) + win->gg.up_down;
	if (h > HEIGHT)
		h = HEIGHT;
	if (y < 0)
	{
		tex = tex_size * (ft_abs(y));
		y = 0;
	}
	while (y < h)
	{
		add_draw(win, x, y, win->img.pos, tex, color);
		tex += tex_size;
		y++;
	}
	draw_floor(x, y, win);
}

void	line_draw(t_main *win, int i, float h, int tex)
{
	int wall_x;

	wall_x = 0;
	if (win->h_is)
		win->img.pos = (int)win->ray.h_dot.pix_x % CUBE;
	else if (win->v_is)
		win->img.pos = (int)win->ray.v_dot.pix_y % CUBE;
	draw(i, h, win, tex);
}
