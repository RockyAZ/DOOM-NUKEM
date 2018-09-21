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

void	render_wall(t_form *form, double start, double end, double len_a, double len_b, t_doom *doom, double width)
{
	double var;
	double pif_a;
	

	var = (a_h - b_h) / width;
	while (start <= end)
	{
		if (start >= 0 && start <= WIDTH)
			draw_line(doom, start, a_h, form);
		a_h -= var;
		start++;
	}
}

void	draw_polygon(t_bsp *bsp, t_player *player, t_doom *doom, int len)
{
	t_vector vect_a;
	t_vector vect_b;
	double	angle_a;
	double	angle_b;

	t_vector	vert_a;//отдельная структура вместо даблов в инт
	t_vector	vert_b;//отдельная структура вместо даблов в инт

	double is_right_a;
	double is_right_b;
	double len_a;
	double len_b;
	double coef;

t_vector cp;
double cp_2;

double pba;
double pab;

double new_len;
double new_len_2;

double check_a;
double check_b;
//заменить корни на квадраты ВЕЗДЕ!!!
	vect_a = normalizing(bsp->node_form->vertex.x1 - player->x, bsp->node_form->vertex.y1 - player->y);
	vect_b = normalizing(bsp->node_form->vertex.x2 - player->x, bsp->node_form->vertex.y2 - player->y);

	angle_a = dot_prod(vect_a.x, vect_a.y, player->view.x, player->view.y);
	angle_b = dot_prod(vect_b.x, vect_b.y, player->view.x, player->view.y);
	angle_a = acos_degree(angle_a);
	angle_b = acos_degree(angle_b);


	vert_a.x = bsp->node_form->vertex.x1;
	vert_a.y = bsp->node_form->vertex.y1;
	vert_b.x = bsp->node_form->vertex.x2;
	vert_b.y = bsp->node_form->vertex.y2;
	if ((player->x == vert_a.x && player->y == vert_a.y) || (player->x == vert_b.x && player->y == vert_b.y))
		return ;
	is_right_a = dot_prod(bsp->node_form->vertex.x1, bsp->node_form->vertex.y1, player->view_right.x, player->view_right.y) - player->normal_right;
	is_right_b = dot_prod(bsp->node_form->vertex.x2, bsp->node_form->vertex.y2, player->view_right.x, player->view_right.y) - player->normal_right;
/*
**	rewrite and optimizing this shit
*/
len_a = pifagor(player->x - vert_a.x, player->y - vert_a.y);
len_b = pifagor(player->x - vert_b.x, player->y - vert_b.y);
pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
pba = 180 - pab - (angle_a + angle_b);
if ((pba <= 0 && angle_a >= 30) && (pba <= 0 && angle_b >= 30))
	return ;

	if (angle_a >= 90 && angle_b >= 90)
		return ;
	else if (is_right_a >= 0 && is_right_b >= 0 && angle_a > 30 && angle_b > 30)
		return ;
	else if (is_right_a <= 0 && is_right_b <= 0 && angle_a > 30 && angle_b > 30)
		return ;
/*
** ALL POINT ON RIGHT SIDE OF SCREEN
*/
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
		len_a = pifagor(player->x - vert_a.x, player->y - vert_a.y);
		len_b = pifagor(player->x - vert_b.x, player->y - vert_b.y);
		if (angle_b > 30)
		{
			coef = ft_max_d(angle_a, angle_b) - ft_min_d(angle_a, angle_b);
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
			coef = bsp->node_form->len / coef;
			new_len = t_cos(len_a, coef * (30 - angle_a), pab);
			render_wall(bsp->node_form, CENTER_W + angle_a * player->angle_coef, WIDTH, len_a, new_len, doom, fabs(angle_a * player->angle_coef - 30 * player->angle_coef));
		}
		else
		{
			angle_a = angle_a * player->angle_coef;
			angle_b = angle_b * player->angle_coef;
			render_wall(bsp->node_form, CENTER_W + angle_a, CENTER_W + angle_b, len_a, len_b, doom, fabs(angle_b - angle_a));
		}
	}
/*
** ALL POINT ON LEFT SIDE OF SCREEN
*/
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
		len_a = pifagor(player->x - vert_a.x, player->y - vert_a.y);
		len_b = pifagor(player->x - vert_b.x, player->y - vert_b.y);
		if (angle_a > 30)
		{
			coef = ft_max_d(angle_a, angle_b) - ft_min_d(angle_a, angle_b);
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
			coef = bsp->node_form->len / coef;
			new_len = t_cos(len_a, coef * (angle_a - 30), pab);
			render_wall(bsp->node_form, 0, CENTER_W - angle_b * player->angle_coef, new_len, len_b, doom, (30 - angle_b) * player->angle_coef);
		}
		else
		{
			angle_a = angle_a * player->angle_coef;
			angle_b = angle_b * player->angle_coef;
			render_wall(bsp->node_form, CENTER_W - angle_a, CENTER_W - angle_b, len_a, len_b, doom, fabs(angle_a - angle_b));
		}
	}
/*
** ONE POINT ON RIGHT SIDE OTHER ON LEFT SIDE OF SCREEN
*/
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
		len_a = pifagor(player->x - vert_a.x, player->y - vert_a.y);
		len_b = pifagor(player->x - vert_b.x, player->y - vert_b.y);
		coef = angle_a + angle_b;
		if (angle_a > 30 && angle_b > 30)
		{
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
			pba = 180 - pab - coef;
			coef = bsp->node_form->len / coef;
/*len_a*/	new_len = t_cos(len_a, coef * (angle_a - 30), pab);
/*len_b*/	new_len_2 = t_cos(len_b, coef * (angle_b - 30), pba);
			render_wall(bsp->node_form, 0, WIDTH, new_len, new_len_2, doom, WIDTH);
		}
		else if (angle_a > 30)
		{
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
			coef = bsp->node_form->len / coef;
			new_len = t_cos(len_a, coef * (angle_a - 30), pab);
			render_wall(bsp->node_form, 0, CENTER_W + angle_b * player->angle_coef, new_len, len_b, doom, 30 * player->angle_coef + angle_b * player->angle_coef);
		}
		else if (angle_b > 30)
		{
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));

			coef = bsp->node_form->len / coef;
			new_len = t_cos(len_a, coef * (30 + angle_a), pab);
			render_wall(bsp->node_form, CENTER_W - angle_a * player->angle_coef, WIDTH, len_a, new_len, doom, angle_a * player->angle_coef + 30 * player->angle_coef);
		}
		else
		{
			angle_a = angle_a * player->angle_coef;
			angle_b = angle_b * player->angle_coef;
			render_wall(bsp->node_form, CENTER_W - angle_a, CENTER_W + angle_b, len_a, len_b, doom, angle_a + angle_b);
		}
	}
}

/*
** BACK - TO - FRONT RENDERING STYLE
*/
void	recursive_draw(t_bsp *bsp, t_player *player, t_doom *doom)
{
	double len;

	if (bsp->is_leaf)
		return ;
	len = (int)dot_prod(bsp->node_form->norm.x, bsp->node_form->norm.y, player->x, player->y) - bsp->node_form->dist;
	if (len > 0)
	{
		recursive_draw(bsp->back, player, doom);
		draw_polygon(bsp, player, doom, len);
		recursive_draw(bsp->front, player, doom);
	}
	else
	{
		recursive_draw(bsp->front, player, doom);
		 if (len != 0)
			draw_polygon(bsp, player, doom, len);
		recursive_draw(bsp->back, player, doom);
	}
}

void	drawing_wall(t_doom *doom)
{
	recursive_draw(doom->bsp, doom->gg, doom);
}

/////////////////////////-->>FRONT-TO-BACK<<--///////////////////////////////////
// void	recursive_draw(t_bsp *bsp, t_player *player, t_screen *scr_buf)
// {
// 	if (bsp->is_leaf)
// 		return ;
// 	if (dot_prod(bsp->node_form->norm.x, bsp->node_form->norm.y, player->x, player->y) - bsp->node_form->dist > 0)
// 	{
// 		recursive_draw(bsp->front, player, scr_buf);
// 	printf("DRAW:%c\n", bsp->node_form->n);
// 		recursive_draw(bsp->back, player, scr_buf);
// 	}
// 	else
// 	{
// 		recursive_draw(bsp->back, player, scr_buf);
// 	printf("DRAW:%c\n", bsp->node_form->n);
// 		recursive_draw(bsp->front, player, scr_buf);
// 	}
// }
