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

void	render_wall(t_form *form, double start, double end, double a_h, double b_h, t_doom *doom, double width)
{
  printf("\nSTART:%f\nEND:%f\nA_H:%f\nB_H:%f\nWIDTH:%f\n", start, end, a_h, b_h, width);

	double var;

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
// printf("HERE!!!\n");
// printf("LEN::%d\n", len);
  printf("+++++++++++++\n");
printf("NAME::%c<<<<<<<<<<_----------------\n", bsp->node_form->n);
printf("P_X:%f\nP_Y:%f\n", player->x, player->y);


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
  printf("angle_a:%f\n", angle_a);
  printf("angle_b:%f\n", angle_b);

printf("IS_RIGHT_A:%f\n", is_right_a);
printf("IS_RIGHT_B:%f\n", is_right_b);
	if (angle_a >= 90 && angle_b >= 90)
		return ;
// else if (angle_a > 30 && angle_b > 90)
	else if (is_right_a >= 0 && is_right_b >= 0 && angle_a > 30 && angle_b > 30)
		return ;
	else if (is_right_a <= 0 && is_right_b <= 0 && angle_a > 30 && angle_b > 30)
		return ;
///////////////////////////////ALL RIGHT
	if (is_right_a >= 0 && is_right_b >= 0)
	{
  printf("RIGHT!!::\n");
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
  printf("LEN_A::%f\nLEN_B::%f\n", len_a, len_b);
		if (angle_b > 30)
		{
			coef = ft_max_d(angle_a, angle_b) - ft_min_d(angle_a, angle_b);
  printf("FIRST_COEF:%f\n", coef);
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
  printf("PAB:%f\n", pab);
			coef = bsp->node_form->len / coef;
  printf("SCEOND_COEF:%f\n", coef);
  printf("len_a:%f\n", len_a);
  printf("angle_a:%f\n", angle_a);
			new_len = t_cos(len_a, coef * (30 - angle_a), pab);
  printf("NEW_LEN:%f\n", new_len);
			render_wall(bsp->node_form, CENTER_W + angle_a * player->angle_coef, WIDTH, WALL / len_a * SCREEN, WALL / new_len * SCREEN, doom, fabs(angle_a * player->angle_coef - 30 * player->angle_coef));
		}
		else
		{
  printf("ELSE!!!\n");
  printf("angle_a:%f\n", angle_a);
  printf("angle_b:%f\n", angle_b);
			angle_a = angle_a * player->angle_coef;
			angle_b = angle_b * player->angle_coef;
			render_wall(bsp->node_form, CENTER_W + angle_a, CENTER_W + angle_b, WALL / len_a * SCREEN, WALL / len_b * SCREEN, doom, fabs(angle_b - angle_a));
		}
	}
///////////////////////////////ALL LEFT
	else if (is_right_a <= 0 && is_right_b <= 0)
	{
  printf("LEFT!!::\n");
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
  printf("LEN_A::%f\nLEN_B::%f\n", len_a, len_b);
		if (angle_a > 30)
		{
			coef = ft_max_d(angle_a, angle_b) - ft_min_d(angle_a, angle_b);
printf("FIRST_COEF:%f\n", coef);
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
printf("PBA:%f\n", pba);
printf("PAB:%f\n", pab);
			coef = bsp->node_form->len / coef;
printf("SCEOND_COEF:%f\n", coef);
printf("len_b:%f\n", len_b);
printf("angle_b:%f\n", angle_b);
printf("pba:%f\n", pba);
			new_len = t_cos(len_a, coef * (angle_a - 30), pab);
			// new_len = t_cos(len_b, bsp->node_form->len - coef * (30 - angle_b), pba);			
printf("NEW_LEN:%f\n", new_len);
/**/		render_wall(bsp->node_form, 0, CENTER_W - angle_b * player->angle_coef, WALL / new_len * SCREEN, WALL / len_b * SCREEN, doom, (30 - angle_b) * player->angle_coef);
		}
		else
		{
printf("ELSE!!!\n");
			angle_a = angle_a * player->angle_coef;
			angle_b = angle_b * player->angle_coef;
			render_wall(bsp->node_form, CENTER_W - angle_a, CENTER_W - angle_b, WALL / len_a * SCREEN, WALL / len_b * SCREEN, doom, fabs(angle_a - angle_b));
		}
	}
///////////////////////////////ONE TO LEFT OTHER TO RIGHT
	else
	{
printf("CENTER!!::\n");
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
printf("ANGLE_A:%f\nANGLE_B:%f\n", angle_a, angle_b);
		coef = angle_a + angle_b;
printf("LEN_A::%f\nLEN_B::%f\n", len_a, len_b);
printf("FIRST_COEF:%f\n", coef);
		if (angle_a > 30 && angle_b > 30)
		{
printf("\nangle_a > 30 && angle_b > 30\n\n");
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
			pba = 180 - pab - coef;
printf("pab:%f<<<<<<<<<<<<<\n", pab);
printf("pba:%f<<<<<<<<<<<<<\n", pba);
			coef = bsp->node_form->len / coef;
printf("SCEOND_COEF:%f\n", coef);
/*len_a*/		new_len = t_cos(len_a, coef * (angle_a - 30), pab);
/*len_b*/		new_len_2 = t_cos(len_b, coef * (angle_b - 30), pba);
printf("NEW_LEN:%f\n", new_len);
printf("NEW_LEN_2:%f\n", new_len_2);
			render_wall(bsp->node_form, 0, WIDTH, WALL / new_len * SCREEN, WALL / new_len_2 * SCREEN, doom, WIDTH);
		}
		else if (angle_a > 30)
		{
printf("\nangle_a > 30\n\n");
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));			
printf("PBA:%f\n", pba);
printf("PAB:%f\n", pab);
			coef = bsp->node_form->len / coef;
printf("SCEOND_COEF:%f\n", coef);
			new_len = t_cos(len_a, coef * (angle_a - 30), pab);
printf("NEW_LEN:%f\n", new_len);
			render_wall(bsp->node_form, 0, CENTER_W + angle_b * player->angle_coef, WALL / new_len * SCREEN, WALL / len_b * SCREEN, doom, 30 * player->angle_coef + angle_b * player->angle_coef);
		}
		else if (angle_b > 30)
		{
printf("\nangle_b > 30\n\n");
			pab = acos_degree((len_a * len_a + bsp->node_form->len * bsp->node_form->len - len_b * len_b) / (2 * len_a * bsp->node_form->len));
printf("PAB:%f\n", pab);

			coef = bsp->node_form->len / coef;
printf("SCEOND_COEF:%f\n", coef);
			new_len = t_cos(len_a, coef * (30 + angle_a), pab);
			render_wall(bsp->node_form, CENTER_W - angle_a * player->angle_coef, WIDTH, WALL / len_a * SCREEN, WALL / new_len * SCREEN, doom, angle_a * player->angle_coef + 30 * player->angle_coef);
		}
		else
		{
printf("ELSE!!!\n");
			angle_a = angle_a * player->angle_coef;
			angle_b = angle_b * player->angle_coef;
			render_wall(bsp->node_form, CENTER_W - angle_a, CENTER_W + angle_b, WALL / len_a * SCREEN, WALL / len_b * SCREEN, doom, angle_a + angle_b);
		}
	}
	printf("ENDED!!!\n");
	printf("\n\n\n");
}

void	recursive_draw(t_bsp *bsp, t_player *player, t_doom *doom)
{
	double len;
	if (bsp->is_leaf)
		return ;
	len = (int)dot_prod(bsp->node_form->norm.x, bsp->node_form->norm.y, player->x, player->y) - bsp->node_form->dist;
	printf("%c\n", bsp->node_form->n);
	printf("DIST::%f\n", bsp->node_form->dist);
	printf("MMAAIINN::LLEENN::::::%f\n", len);
	printf("DOT::%f\n, dist:%f\n", dot_prod(bsp->node_form->norm.x, bsp->node_form->norm.y, player->x, player->y), bsp->node_form->dist);
	if (len > 0)
	{
printf("FIRST\n");
		recursive_draw(bsp->back, player, doom);
		draw_polygon(bsp, player, doom, len);
		recursive_draw(bsp->front, player, doom);
	}
	else
	{
printf("SECOND\n");
		recursive_draw(bsp->front, player, doom);
		 if (len != 0)
			draw_polygon(bsp, player, doom, len);
		recursive_draw(bsp->back, player, doom);
	}
}

void	drawing_wall(t_doom *doom)
{
	recursive_draw(doom->bsp, doom->gg, doom);
	printf("===========================================================\n");
}
