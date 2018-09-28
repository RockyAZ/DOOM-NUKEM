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


int get_line_intersection(double p0_x, double p0_y, double p1_x, double p1_y, double p2_x, double p2_y, double p3_x, double p3_y, double *i_x, double *i_y)
{
	double s1_x, s1_y, s2_x, s2_y;
	s1_x = p1_x - p0_x;
	s1_y = p1_y - p0_y;

	s2_x = p3_x - p2_x;
	s2_y = p3_y - p2_y;

	double s, t;
	s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);
	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		if (i_x != NULL)
			*i_x = p0_x + (t * s1_x);
		if (i_y != NULL)
			*i_y = p0_y + (t * s1_y);
		return 1;
	}
	return 0;
}


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

int		some_line(t_main *win, int v, int h, double angle, t_lines *line)
{
	t_lines	gg_line;

	if (win->v_is)
	{
		gg_line.x1 = win->gg.p_x;
		gg_line.y1 = win->gg.p_y;
		gg_line.x2 = win->ray.v_dot.pix_x;
		gg_line.y2 = win->ray.v_dot.pix_y;
	}
	else
	{
		gg_line.x1 = win->gg.p_x;
		gg_line.y1 = win->gg.p_y;
		gg_line.x2 = win->ray.h_dot.pix_x;
		gg_line.y2 = win->ray.h_dot.pix_y;
	}
	win->l_p = lineLineIntersection(gg_line, *line);
	if (win->l_p.x <= 0 || win->l_p.y <= 0 || win->l_p.x > win->data->col * CUBE || win->l_p.y > win->data->line * CUBE)
		return (0);
	if (!get_line_intersection(gg_line.x1, gg_line.y1, gg_line.x2, gg_line.y2, line->x1, line->y1, line->x2, line->y2, NULL, NULL))
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
		casting_draw(win, i, ((double)CUBE / (double)h) * win->gg.to_screen, win->data->map[win->ray.h_dot.real_y][win->ray.h_dot.real_x]);
	else
		casting_draw(win, i, ((double)CUBE / (double)v) * win->gg.to_screen, win->data->map[win->ray.v_dot.real_y][win->ray.v_dot.real_x]);
}

void	ray_simple(t_main *win, double angle, int v, int h)
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
		if (some_line(win, v, h, angle, &win->line[0]))
			casting_draw(win , i, ((double)CUBE / (double)pifagor(win, angle, 'l')) * win->gg.to_screen, -2);
		else if (some_line(win, v, h, angle, &win->line[1]))
			casting_draw(win , i, ((double)CUBE / (double)pifagor(win, angle, 'l')) * win->gg.to_screen, -2);
		else if (some_line(win, v, h, angle, &win->line[2]))
			casting_draw(win , i, ((double)CUBE / (double)pifagor(win, angle, 'l')) * win->gg.to_screen, -2);
		// else
			// call_drawer(win, i, v, h);
win->hy = 0;
		angle -= win->gg.angle_size;
	}
}
