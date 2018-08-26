/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 16:48:42 by azaporoz          #+#    #+#             */
/*   Updated: 2018/08/16 16:48:43 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_param(t_main *win, int v, int h)
{
	if (v < 0)
		win->h_is = 1;
	else if (h < 0)
		win->v_is = 1;
	else
	{
		if (v < h)
			win->v_is = 1;
		else if (h < v)
			win->h_is = 1;
	}
	// if (win->ray.angle == win->gg.angle)
		// ft_putnbr_end(win->gg.angle);
}

void	call_drawer(t_main *win, int i, int v, int h)
{
	if (win->h_is)
		line_draw(win, i, ((float)CUBE / (float)h) * win->gg.to_screen,\
		win->data->map[win->ray.h_dot.real_y][win->ray.h_dot.real_x]);
	else if (win->v_is)
		line_draw(win, i, ((float)CUBE / (float)v) * win->gg.to_screen,\
		win->data->map[win->ray.v_dot.real_y][win->ray.v_dot.real_x]);
	else
		line_draw(win, i, ((float)CUBE / (float)h) * win->gg.to_screen,\
		win->data->map[win->ray.h_dot.real_y][win->ray.h_dot.real_x]);
}

void	ray_simple(t_main *win, float angle, int v, int h)
{
	int	i;

	i = -1;
	angle = win->gg.angle + (win->gg.fov / 2);
	while (++i < WIDTH)
	{
win->hy = 0;	
if (i == WIDTH / 2)
win->hy = 1;
		win->v_is = 0;
		win->h_is = 0;
		if (angle >= 360)
			angle -= 360;
		if (angle < 0)
			angle += 360;
		win->ray.angle = angle;
		if (angle > 0 && angle < 180)
			h = horiz_inter_top(win, angle);
		else if (angle > 180 && angle < 360)
			h = horiz_inter_bot(win, angle);
		if (angle > 90 && angle < 270)
			v = vertic_inter_left(win, angle);
		else if (angle > 270 || angle < 90)
			v = vertic_inter_right(win, angle);
		set_param(win, v, h);
		call_drawer(win, i, v, h);
win->hy = 0;	
		angle -= win->gg.angle_size;
	}
}
