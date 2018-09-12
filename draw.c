/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 16:37:45 by azaporoz          #+#    #+#             */
/*   Updated: 2018/09/12 16:37:45 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned int	get_pixel(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;

	pixels = (unsigned int*)surface->pixels;
	return (pixels[(y * surface->w) + x]);
}

void	draw_line(t_doom *doom, int x, double h, t_form *form)
{
	int y;
	int j;

	y = CENTER_H - h / 2;
	j = CENTER_H + h / 2;
	if (y < 0)
		y = 0;
	if (j > HEIGHT)
	j = HEIGHT;
	while (y < j)
	{
		doom->buffer[y][x] = form->color;
		y++;
	}
}

void	renderer_left(t_form *form, double start, double end, double a_h, double b_h, t_doom *doom)
{
	// double pif_a;
	// double pif_b;
	double var;
	double width = start - end;

	width = fabs(width);
	// pif_a = pifagor(form->vertex.x1 - player->x, form->vertex.y1 - player->y);
	// pif_b = pifagor(form->vertex.x2 - player->x, form->vertex.y2 - player->y);
	// a_h = WALL / pif_a * SCREEN;
	// b_h = WALL / pif_b * SCREEN;
	var = (a_h - b_h) / width;
	start = CENTER_W - start;
	end = CENTER_W - end;
	while (start <= end)
	{
		if (start >= 0 && start <= WIDTH)
			draw_line(doom, start, a_h, form);
		a_h -= var;
		start++;
	}
}

void	draw_polygon(t_bsp *bsp, t_player *player, t_doom *doom)
{
	t_vector vect_a;
	t_vector vect_b;
	double	angle_a;
	double	angle_b;

	t_vect	vert_a;//отдельная структура вместо даблов в инт
	t_vect	vert_b;//отдельная структура вместо даблов в инт

	double is_right_a;
	double is_right_b;
	double len_a;
	double len_b;
	double coef;
t_vector cp;
double cp_2;

double pba;
double pab;

	vect_a = normalizing(bsp->node_form->vertex.x1 - player->x, bsp->node_form->vertex.y1 - player->y);
	vect_b = normalizing(bsp->node_form->vertex.x2 - player->x, bsp->node_form->vertex.y2 - player->y);
	angle_a = acos(dot_prod(vect_a.x, vect_a.y, player->view.x, player->view.y));
	angle_b = acos(dot_prod(vect_b.x, vect_b.y, player->view.x, player->view.y));
	if (angle_a >= 90 && angle_b >= 90)
		return ;
	else if (is_right_a >= 0 && is_right_b >= 0 && angle_a > 30 && angle_b > 30)
		return ;
	else if (is_right_a <= 0 && is_right_b <= 0 && angle_a > 30 && angle_b > 30)
		return ;
	vert_a.x = bsp->node_form->vertex.x1;
	vert_a.y = bsp->node_form->vertex.y1;
	vert_b.x = bsp->node_form->vertex.x2;
	vert_b.y = bsp->node_form->vertex.y2;
	is_right_a = dot_prod(bsp->node_form->vertex.x1, bsp->node_form->vertex.y1, player->view_right.x, player->view_right.y) - player->normal_right;
	is_right_b = dot_prod(bsp->node_form->vertex.x2, bsp->node_form->vertex.y2, player->view_right.x, player->view_right.y) - player->normal_right;
	// if (is_right_a > 0 && is_right_b > 0)
	// {
	// 	if (angle_a > angle_b)
	// 	{
	// 		cp = vert_a;
	// 		vert_a = vert_b;
	// 		vert_b = cp;
	// 	}
	// }
	// else if (is_right_a < 0 && is_right_b < 0)
	// {
	// 	if (angle_a < angle_b)
	// 	{
	// 		cp = vert_a;
	// 		vert_a = vert_b;
	// 		vert_b = cp;
	// 	}
	// }
	// else if (is_right_a > 0 && is_right_b < 0)
	// {
	// 	cp = vert_a;
	// 	vert_a = vert_b;
	// 	vert_b = cp;
	// }
	if (is_right_a >= 0 && is_right_b >= 0)
	{
		if (angle_a > angle_b)
		{
			cp = vert_a;
			vert_a = vert_b;
			vert_b = cp;
			cp_2 = angle_a;
			angle_a = angle_b;
			angle_b = cp_2;
		}
		coef = ft_max_d(angle_a, angle_b) - ft_min_d(angle_a, angle_b);
		coef = bsp->node_form->len / coef;
	len_a = pifagor(player->x - vert_a.x, player->y - vert_a.y);
	len_b = pifagor(player->x - vert_b.x, player->y - vert_b.y);
		angle_a = angle_a * player->angle_coef;
		angle_b = angle_b * player->angle_coef;
		renderer_right(bsp->node_form, player, ft_min_d(angle_a, angle_b), ft_max_d(angle_a, angle_b), doom);
	}
	else if (is_right_a <= 0 && is_right_b <= 0)
	{
		if (angle_a < angle_b)
		{
			cp = vert_a;
			vert_a = vert_b;
			vert_b = cp;
			cp_2 = angle_a;
			angle_a = angle_b;
			angle_b = cp_2;
		}
		coef = ft_max_d(angle_a, angle_b) - ft_min_d(angle_a, angle_b);
		coef = bsp->node_form->len / coef;
		if (angle_a > 30)
			coef = 30 * coef;
	len_a = pifagor(player->x - vert_a.x, player->y - vert_a.y);
	len_b = pifagor(player->x - vert_b.x, player->y - vert_b.y);
		angle_a = angle_a * player->angle_coef;
		angle_b = angle_b * player->angle_coef;
		renderer_left(bsp->node_form, angle_a, angle_b, h_a, h_b, doom);
	}
	else
	{
		if (is_right_a > 0 && is_right_b < 0)
		{
			cp = vert_a;
			vert_a = vert_b;
			vert_b = cp;
			cp_2 = angle_a;
			angle_a = angle_b;
			angle_b = cp_2;
		}
		coef = angle_a + angle_b;
		coef = bsp->node_form->len / coef;
	len_a = pifagor(player->x - vert_a.x, player->y - vert_a.y);
	len_b = pifagor(player->x - vert_b.x, player->y - vert_b.y);
		angle_a = angle_a * player->angle_coef;
		angle_b = angle_b * player->angle_coef;
		if (is_right_a < 0)
			renderer_center(bsp->node_form, player, angle_a, angle_b, doom);
		else
			renderer_center(bsp->node_form, player, angle_b, angle_a, doom);
	}
}

void	recursive_draw(t_bsp *bsp, t_player *player, t_doom *doom)
{
	if (bsp->is_leaf)
		return ;
	if (dot_prod(bsp->node_form->norm.x, bsp->node_form->norm.y, player->x, player->y) - bsp->node_form->dist > 0)
	{
		recursive_draw(bsp->back, player, doom);
		draw_polygon(bsp, player, doom);
		recursive_draw(bsp->front, player, doom);
	}
	else
	{
		recursive_draw(bsp->front, player, doom);
		draw_polygon(bsp, player, doom);
		recursive_draw(bsp->back, player, doom);
	}
}

void	drawing_wall(t_doom *doom)
{
	recursive_draw(doom->bsp, doom->gg, doom);
}
