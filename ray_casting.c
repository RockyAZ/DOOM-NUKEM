/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:14:26 by azaporoz          #+#    #+#             */
/*   Updated: 2018/07/30 13:14:26 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		vertic_inter_left(t_main *win, float angle)
{
	win->ray.v_dot.pix_x = (((int)win->gg.p_x >> BIT) << BIT) - 1;
	if (angle == 180)
		win->ray.v_dot.pix_y = win->gg.p_y;
	else
		win->ray.v_dot.pix_y = win->gg.p_y +\
		(win->gg.p_x - win->ray.v_dot.pix_x) * ft_tan(angle);
	if (win->ray.v_dot.pix_y >= win->data->m_y || win->ray.v_dot.pix_y < 0)
		return (-1);
	win->ray.v_dot.real_x = (int)win->ray.v_dot.pix_x >> BIT;
	win->ray.v_dot.real_y = (int)win->ray.v_dot.pix_y >> BIT;
	win->ray.v_dot.var_x = -CUBE;
	if (angle == 180)
		win->ray.v_dot.var_y = 0;
	win->ray.v_dot.var_y = CUBE * ft_tan(angle);
	while (win->data->map[win->ray.v_dot.real_y][win->ray.v_dot.real_x] == 0)
	{
		win->ray.v_dot.pix_y += win->ray.v_dot.var_y;
		win->ray.v_dot.pix_x += win->ray.v_dot.var_x;
		win->ray.v_dot.real_x = (int)win->ray.v_dot.pix_x >> BIT;
		win->ray.v_dot.real_y = (int)win->ray.v_dot.pix_y >> BIT;
		if (win->ray.v_dot.pix_y >= win->data->m_y || win->ray.v_dot.pix_y < 0)
			return (-1);
	}
	return (pifagor(win, angle, 'v'));
}

int		vertic_inter_right(t_main *win, float angle)
{
	win->ray.v_dot.pix_x = (((int)win->gg.p_x >> BIT) << BIT) + CUBE;
	if (angle == 0)
		win->ray.v_dot.pix_y = win->gg.p_y;
	else
		win->ray.v_dot.pix_y = win->gg.p_y +\
		(win->gg.p_x - win->ray.v_dot.pix_x) * ft_tan(angle);
	if (win->ray.v_dot.pix_y >= win->data->m_y || win->ray.v_dot.pix_y < 0)
		return (-1);
	win->ray.v_dot.real_x = (int)win->ray.v_dot.pix_x >> BIT;
	win->ray.v_dot.real_y = (int)win->ray.v_dot.pix_y >> BIT;
	win->ray.v_dot.var_x = CUBE;
	if (angle == 0)
		win->ray.v_dot.var_y = 0;
	win->ray.v_dot.var_y = (CUBE * ft_tan(angle)) * -1;
	while (win->data->map[win->ray.v_dot.real_y][win->ray.v_dot.real_x] == 0)
	{
		win->ray.v_dot.pix_y += win->ray.v_dot.var_y;
		win->ray.v_dot.pix_x += win->ray.v_dot.var_x;
		win->ray.v_dot.real_x = (int)win->ray.v_dot.pix_x >> BIT;
		win->ray.v_dot.real_y = (int)win->ray.v_dot.pix_y >> BIT;
		if (win->ray.v_dot.pix_y >= win->data->m_y || win->ray.v_dot.pix_y < 0)
			return (-1);
	}
	return (pifagor(win, angle, 'v'));
}

int		horiz_inter_top(t_main *win, float angle)
{
	win->ray.h_dot.pix_y = (((int)win->gg.p_y >> BIT) << BIT) - 1;
	if (angle == 90)
		win->ray.h_dot.pix_x = win->gg.p_x;
	else
		win->ray.h_dot.pix_x = win->gg.p_x +\
		(win->gg.p_y - win->ray.h_dot.pix_y) / ft_tan(angle);
	if (win->ray.h_dot.pix_x >= win->data->m_x || win->ray.h_dot.pix_x < 0)
		return (-1);
	win->ray.h_dot.real_x = (int)win->ray.h_dot.pix_x >> BIT;
	win->ray.h_dot.real_y = (int)win->ray.h_dot.pix_y >> BIT;
	if (angle == 90)
		win->ray.h_dot.var_x = 0;
	else
		win->ray.h_dot.var_x = CUBE / ft_tan(angle);
	win->ray.h_dot.var_y = -CUBE;
	while (win->data->map[win->ray.h_dot.real_y][win->ray.h_dot.real_x] == 0)
	{
		win->ray.h_dot.pix_x += win->ray.h_dot.var_x;
		win->ray.h_dot.pix_y += win->ray.h_dot.var_y;
		win->ray.h_dot.real_x = (int)win->ray.h_dot.pix_x >> BIT;
		win->ray.h_dot.real_y = (int)win->ray.h_dot.pix_y >> BIT;
		if (win->ray.h_dot.pix_x >= win->data->m_x || win->ray.h_dot.pix_x < 0)
			return (-1);
	}
	return (pifagor(win, angle, 'h'));
}

int		horiz_inter_bot(t_main *win, float angle)
{
	win->ray.h_dot.pix_y = (((int)win->gg.p_y >> BIT) << BIT) + CUBE;
	if (angle == 270)
		win->ray.h_dot.pix_x = win->gg.p_x;
	else
		win->ray.h_dot.pix_x = win->gg.p_x +\
		(win->gg.p_y - win->ray.h_dot.pix_y) / ft_tan(angle);
	if (win->ray.h_dot.pix_x >= win->data->m_x || win->ray.h_dot.pix_x < 0)
		return (-1);
	win->ray.h_dot.real_x = (int)win->ray.h_dot.pix_x >> BIT;
	win->ray.h_dot.real_y = (int)win->ray.h_dot.pix_y >> BIT;
	if (angle == 270)
		win->ray.h_dot.var_x = 0;
	else
		win->ray.h_dot.var_x = (CUBE / ft_tan(angle)) * -1;
	win->ray.h_dot.var_y = CUBE;
	while (win->data->map[win->ray.h_dot.real_y][win->ray.h_dot.real_x] == 0)
	{
		win->ray.h_dot.pix_x += win->ray.h_dot.var_x;
		win->ray.h_dot.pix_y += win->ray.h_dot.var_y;
		win->ray.h_dot.real_x = (int)win->ray.h_dot.pix_x >> BIT;
		win->ray.h_dot.real_y = (int)win->ray.h_dot.pix_y >> BIT;
		if (win->ray.h_dot.pix_x >= win->data->m_x || win->ray.h_dot.pix_x < 0)
			return (-1);
	}
	return (pifagor(win, angle, 'h'));
}

void	ray_casting(t_main *win)
{
	float	angle;
	int		v;
	int		h;

	angle = 0;
	v = -1;
	h = -1;
	ray_simple(win, angle, v, h);
}
