/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 16:34:28 by azaporoz          #+#    #+#             */
/*   Updated: 2018/08/03 16:34:29 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	moving_up(t_main *win, int lr)
{
	float	p_x;
	float	p_y;
	int		f_x;
	int		f_y;

	p_x = win->gg.p_x;
	p_y = win->gg.p_y;
	if (win->gg.angle <= 270 && win->gg.angle >= 90)
		f_x = -FACE;
	else
		f_x = FACE;
	if (win->gg.angle <= 180 && win->gg.angle >= 0)
		f_y = -FACE;
	else
		f_y = FACE;
	if (win->keys.up || win->keys.w || lr)
	{
		p_x += win->gg.speed * ft_cos(win->gg.angle) + f_x;
		if (!(win->data->map[(int)win->gg.p_y >> BIT][(int)p_x >> BIT]))
			win->gg.p_x = p_x - f_x;
		p_y += win->gg.speed * (ft_sin(win->gg.angle) * -1) + f_y;
		if (!(win->data->map[(int)p_y >> BIT][(int)win->gg.p_x >> BIT]))
			win->gg.p_y = p_y - f_y;
	}
}

void	moving_down(t_main *win)
{
	float p_x;
	float p_y;

	p_x = win->gg.p_x;
	p_y = win->gg.p_y;
	if (win->keys.down || win->keys.s)
	{
		p_x -= win->gg.speed * ft_cos(win->gg.angle);
		if (!(win->data->map[(int)win->gg.p_y >> BIT][(int)p_x >> BIT]))
			win->gg.p_x = p_x;
		p_y -= win->gg.speed * (ft_sin(win->gg.angle) * -1);
		if (!(win->data->map[(int)p_y >> BIT][(int)win->gg.p_x >> BIT]))
			win->gg.p_y = p_y;
	}
}

void	moving_side(t_main *win)
{
	if (win->keys.a || win->keys.d)
	{
		if (win->keys.a)
			win->gg.angle += 90;
		if (win->keys.d)
			win->gg.angle -= 90;
		if (win->gg.angle >= 360)
			win->gg.angle -= 360;
		if (win->gg.angle < 0)
			win->gg.angle += 360;
		moving_up(win, 1);
		if (win->keys.a)
			win->gg.angle -= 90;
		if (win->keys.d)
			win->gg.angle += 90;
		if (win->gg.angle >= 360)
			win->gg.angle -= 360;
		if (win->gg.angle < 0)
			win->gg.angle += 360;
	}
}

void	active_keys(t_main *win)
{
	if (win->keys.right)
	{
		win->gg.angle -= win->rotate;
		if (win->gg.angle > 360)
			win->gg.angle -= 360;
	}
	if (win->keys.left)
	{
		win->gg.angle += win->rotate;
		if (win->gg.angle < 0)
			win->gg.angle += 360;
	}
	if (win->gg.angle >= 360)
		win->gg.angle -= 360;
	if (win->gg.angle < 0)
		win->gg.angle += 360;
	moving_up(win, 0);
	moving_down(win);
	moving_side(win);
	win->gg.r_x = (int)win->gg.p_x >> BIT;
	win->gg.r_y = (int)win->gg.p_y >> BIT;
}
