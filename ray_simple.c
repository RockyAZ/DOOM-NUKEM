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



t_mouse lineLineIntersection(t_lines a, t_lines b)
{
    double a1 = a.y2 - a.y1;
    double b1 = a.x1 - a.x2;
    double c1 = a1 * (a.x1) + b1 * (a.y1);
    double a2 = b.y2 - b.y1;
    double b2 = b.x1 - b.x2;
    double c2 = a2 * (b.x1) + b2 * (b.y1);
    double determinant = a1*b2 - a2*b1;

	t_mouse		res;

	if (determinant == 0)
	{
		res.x = 0;
		res.y = 0;
		return (res);
	}
    else
    {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
		res.x = x;
		res.y = y;
        return (res);
    }
}

int		some_line(t_main *win, int v, int h, float angle)
{
	t_lines	gg_line;

	if (win->v_is)
	{
if (win->hy)
write(1, "a", 1);
		gg_line.x1 = win->gg.p_x;
		gg_line.y1 = win->gg.p_y;
		gg_line.x2 = win->ray.h_dot.pix_x;
		gg_line.y2 = win->ray.h_dot.pix_y;
	}
	else
	{
if (win->hy)
write(1, "b", 1);
		gg_line.x1 = win->gg.p_x;
		gg_line.y1 = win->gg.p_y;
		gg_line.x2 = win->ray.v_dot.pix_x;
		gg_line.y2 = win->ray.v_dot.pix_y;
	}
	win->l_p = lineLineIntersection(gg_line, win->line);
if (win->hy)
{
printf("GG_ANGLE:%f\nGG_POS_X:%f\nGG_POS_Y:%f\n"m win->gg.angle, win->gg.p_x, win->p_y);
printf("ax1:%d ay1:%d ax2:%d ay2:%d bx1:%d by1:%d bx2:%d by2:%d \nX:%d\nY:%d\n\n", gg_line.x1, gg_line.y1, gg_line.x2, gg_line.y2, win->line.x1, win->line.y1, win->line.x2, win->line.y2, win->l_p.x, win->l_p.y);
}
	if (!win->l_p.x && !win->l_p.y)
		return (0);
	return (1);
}

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
}

void	call_drawer(t_main *win, int i, int v, int h)
{
	if (win->h_is)
		casting_draw(win, i, ((float)CUBE / (float)h) * win->gg.to_screen, win->data->map[win->ray.h_dot.real_y][win->ray.h_dot.real_x]);
	else if (win->v_is)
		casting_draw(win, i, ((float)CUBE / (float)v) * win->gg.to_screen,\
		win->data->map[win->ray.v_dot.real_y][win->ray.v_dot.real_x]);
	else
		casting_draw(win, i, ((float)CUBE / (float)h) * win->gg.to_screen,\
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
		if (some_line(win, v, h, angle))
			casting_draw(win , i, ((float)CUBE / (float)pifagor(win, angle, 'l')) * win->gg.to_screen, 2);
		else
		// {write(1, "a\n", 2);
			call_drawer(win, i, v, h);
		// }
win->hy = 0;
		angle -= win->gg.angle_size;
	}
}
