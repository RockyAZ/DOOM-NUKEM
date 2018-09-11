/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 20:49:58 by azaporoz          #+#    #+#             */
/*   Updated: 2018/09/05 20:50:01 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// void	recursive_draw(t_bsp *bsp, t_player *player, t_screen *scr_buf)
// {
// 	if (dot_prod(bsp->node_form->norm.x, bsp->node_form->norm.y, player->x, player->y) - bsp->node_form->dist > 0)
// 	{
// 		if (bsp->front->is_leaf)
// 		{
// 			player->pos = bsp;
// 			player->front = 1;
// printf("DRAW:%c\n", bsp->node_form->n);
// 			return ;
// 		}
// 		recursive_draw(bsp->front, player, scr_buf);
// 	}
// 	else
// 	{
// 		if (bsp->back->is_leaf)
// 		{
// 			player->pos = bsp;
// 			player->front = 0;
// printf("DRAW:%c\n", bsp->node_form->n);
// 			return ;
// 		}
// 		recursive_draw(bsp->back, player, scr_buf);
// 	}
// printf("DRAW:%c\n", bsp->node_form->n);
// }

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
// printf("H:%f<<<<<<<<<\n", h);
	y = CENTER_H - h / 2;
	j = CENTER_H + h / 2;
	if (y < 0)
		y = 0;
	if (j > HEIGHT)
	j = HEIGHT;
	while (y < j)
	{
// printf("X:%f\nY:%f\n", x, y);
		// doom->buffer[y][x] = get_pixel(win->img.tex[color], tex_x, tex_y);
		doom->buffer[y][x] = form->color;
		y++;
	}
}

void	renderer_center(t_form *form, t_player *player, double start, double end, t_doom *doom)
{
	printf("CANTER DRAWING!!!!!!!!!!!!!!\n");
	double pif_a;
	double pif_b;
	double a_h;
	double b_h;
	double var;
	double width = start + end;
printf("REAL_START:%f\nREAL_END:%f\n", start, end);
printf("\nvertex.x1::%d\nvertex.y1::%d\nvertex.x2::%d\nvertex.y2::%d\nplayer->x::%f\nplayer->y::%f\n\n", form->vertex.x1, form->vertex.y1, form->vertex.x2, form->vertex.y2, player->x, player->y);
	pif_a = pifagor(form->vertex.x1 - player->x, form->vertex.y1 - player->y);
	pif_b = pifagor(form->vertex.x2 - player->x, form->vertex.y2 - player->y);
double dot_a = dot_prod(player->x, player->y, form->norm.x, form->norm.y);
double dot_b = dot_prod(player->x, player->y, form->norm.x, form->norm.y);
printf("DOT_A:%f\nDOT_B:%f\nDIST:%f\n", dot_a, dot_b, form->dist);
printf("normal_vect_x::%f\nnormal_vect_y::%f\n", form->norm.x, form->norm.y);
	a_h = WALL / pif_a / pifagor(form->center.x - player->x, form->center.y - player->y) * SCREEN;
	b_h = WALL / pif_b / pifagor(form->center.x - player->x, form->center.y - player->y) * SCREEN;
	// a_h = WALL / pif_a / (dot_prod(player->x, player->y, form->norm.x, form->norm.y) - form->dist) * SCREEN;
	// b_h = WALL / pif_b / (dot_prod(player->x, player->y, form->norm.x, form->norm.y) - form->dist) * SCREEN;
	// a_h = WALL / pif_a * SCREEN;
	// b_h = WALL / pif_b * SCREEN;
	var = (a_h - b_h) / width;
	start = CENTER_W - start;
	end = CENTER_W + end;
printf("2START::%f\n", start);
printf("2END::%f\n", end);
printf("PIF_A:%f\n", pif_a);
printf("PIF_B:%f\n", pif_b);
printf("HEIGHT_A:%f<<--\n", a_h);
printf("HEIGHT_B:%f<<--\n", b_h);
printf("VAR:%f\n", var);
printf("WIDTH:%f<<--\n", width);
printf("player->angle_coef::%f\n", player->angle_coef);
printf("P_X::%f\nP_Y::%f\n", player->x, player->y);
printf("VIEW_x::%f\nVIEW_y::%f\n", player->view.x, player->view.y);
printf("RIGHT_VIEW_x::%f\nRIGHT_VIEW_y::%f\n", player->view_right.x, player->view_right.y);
printf("NORMAL::%f\nNORMAL_RIGHT:%f\n", player->normal, player->normal_right);
	while (start <= end)
	{
		if (start >= 0 && start <= WIDTH)
			draw_line(doom, start, a_h, form);
		a_h -= var;
		start++;
	}
	printf("___%f\n", a_h);
}

void	renderer_left(t_form *form, t_player *player, double start, double end, t_doom *doom)
{
	printf("LEFT DRAWING!!!!!!!!!!!!!!\n");
	double pif_a;
	double pif_b;
	double a_h;
	double b_h;
	double var;
	double width = start - end;
	width = fabs(width);
printf("REAL_START:%f\nREAL_END:%f\n", start, end);
printf("\nvertex.x1::%d\nvertex.y1::%d\nvertex.x2::%d\nvertex.y2::%d\nplayer->x::%f\nplayer->y::%f\n\n", form->vertex.x1, form->vertex.y1, form->vertex.x2, form->vertex.y2, player->x, player->y);
	pif_a = pifagor(form->vertex.x1 - player->x, form->vertex.y1 - player->y);
	pif_b = pifagor(form->vertex.x2 - player->x, form->vertex.y2 - player->y);
double dot_a = dot_prod(player->x, player->y, form->norm.x, form->norm.y);
double dot_b = dot_prod(player->x, player->y, form->norm.x, form->norm.y);
printf("DOT_A:%f\nDOT_B:%f\nDIST:%f\n", dot_a, dot_b, form->dist);
printf("normal_vect_x::%f\nnormal_vect_y::%f\n", form->norm.x, form->norm.y);
	a_h = WALL / pif_a / pifagor(form->center.x - player->x, form->center.y - player->y) * SCREEN;
	b_h = WALL / pif_b / pifagor(form->center.x - player->x, form->center.y - player->y) * SCREEN;
	// a_h = WALL / pif_a / (dot_prod(player->x, player->y, form->norm.x, form->norm.y) - form->dist) * SCREEN;
	// b_h = WALL / pif_b / (dot_prod(player->x, player->y, form->norm.x, form->norm.y) - form->dist) * SCREEN;
	// a_h = WALL / pif_a * SCREEN;
	// b_h = WALL / pif_b * SCREEN;
	var = (a_h - b_h) / width;
	start = CENTER_W - start;
	end = CENTER_W - end;
printf("2START::%f\n", start);
printf("2END::%f\n", end);
printf("PIF_A:%f\n", pif_a);
printf("PIF_B:%f\n", pif_b);
printf("HEIGHT_A:%f<<--\n", a_h);
printf("HEIGHT_B:%f<<--\n", b_h);
printf("VAR:%f\n", var);
printf("WIDTH:%f<<--\n", width);
printf("player->angle_coef::%f\n", player->angle_coef);
printf("P_X::%f\nP_Y::%f\n", player->x, player->y);
printf("VIEW_x::%f\nVIEW_y::%f\n", player->view.x, player->view.y);
printf("RIGHT_VIEW_x::%f\nRIGHT_VIEW_y::%f\n", player->view_right.x, player->view_right.y);
printf("NORMAL::%f\nNORMAL_RIGHT:%f\n", player->normal, player->normal_right);

	while (start <= end)
	{
		if (start >= 0 && start <= WIDTH)
			draw_line(doom, start, a_h, form);
		a_h -= var;
		start++;
	}
	printf("___%f\n", a_h);
}

void	renderer_right(t_form *form, t_player *player, double start, double end, t_doom *doom)
{
	printf("RIGHT DRAWING!!!!!!!!!!!!!!\n");
	double pif_a;
	double pif_b;
	double a_h;
	double b_h;
	double var;
	double width = start - end;
	width = fabs(width);
printf("REAL_START:%f\nREAL_END:%f\n", start, end);	
printf("\nvertex.x1::%d\nvertex.y1::%d\nvertex.x2::%d\nvertex.y2::%d\nplayer->x::%f\nplayer->y::%f\n\n", form->vertex.x1, form->vertex.y1, form->vertex.x2, form->vertex.y2, player->x, player->y);
	pif_a = pifagor(form->vertex.x1 - player->x, form->vertex.y1 - player->y);
	pif_b = pifagor(form->vertex.x2 - player->x, form->vertex.y2 - player->y);
double dot_a = dot_prod(player->x, player->y, form->norm.x, form->norm.y);
double dot_b = dot_prod(player->x, player->y, form->norm.x, form->norm.y);
printf("DOT_A:%f\nDOT_B:%f\nDIST:%f\n", dot_a, dot_b, form->dist);
printf("normal_vect_x::%f\nnormal_vect_y::%f\n", form->norm.x, form->norm.y);
	a_h = WALL / pif_a / pifagor(form->center.x - player->x, form->center.y - player->y) * SCREEN;
	b_h = WALL / pif_b / pifagor(form->center.x - player->x, form->center.y - player->y) * SCREEN;
	// a_h = WALL / pif_a / (dot_prod(player->x, player->y, form->norm.x, form->norm.y) - form->dist) * SCREEN;
	// b_h = WALL / pif_b / (dot_prod(player->x, player->y, form->norm.x, form->norm.y) - form->dist) * SCREEN;
	// a_h = WALL / pif_a * SCREEN;
	// b_h = WALL / pif_b * SCREEN;
	var = (a_h - b_h) / width;
	start = CENTER_W + start;
	end = CENTER_W + end;
printf("2START::%f\n", start);
printf("2END::%f\n", end);
printf("PIF_A:%f\n", pif_a);
printf("PIF_B:%f\n", pif_b);
printf("HEIGHT_A:%f<<--\n", a_h);
printf("HEIGHT_B:%f<<--\n", b_h);
printf("VAR:%f\n", var);
printf("WIDTH:%f<<--\n", width);
printf("player->angle_coef::%f\n", player->angle_coef);
printf("P_X::%f\nP_Y::%f\n", player->x, player->y);
printf("VIEW_x::%f\nVIEW_y::%f\n", player->view.x, player->view.y);
printf("RIGHT_VIEW_x::%f\nRIGHT_VIEW_y::%f\n", player->view_right.x, player->view_right.y);
printf("NORMAL::%f\nNORMAL_RIGHT:%f\n", player->normal, player->normal_right);
	while (start <= end)
	{
		if (start >= 0 && start <= WIDTH)
			draw_line(doom, start, a_h, form);
		a_h -= var;
		start++;
	}
	printf("___%f\n", a_h);
}

/*	отношение градуса к экарну занести в таблицу	*/
/////////////////////////-->>BACK-TO-FRONT<<--///////////////////////////////////
void	draw_polygon(t_bsp *bsp, t_player *player, t_doom *doom)
{
	double	angle_a;
	double	angle_b;
	t_vector vect_a;
	t_vector vect_b;
	double is_right_a;
	double is_right_b;

	printf("bsp->node_form->vertex.x1::%d, bsp->node_form->vertex.y1::%d, player->view_right.x::%f, player->view_right.y::%f) - player->normal_right::%f\n",\
	bsp->node_form->vertex.x1, bsp->node_form->vertex.y1, player->view_right.x, player->view_right.y, player->normal_right);
	printf("bsp->node_form->vertex.x2::%d, bsp->node_form->vertex.y2::%d, player->view_right.x::%f, player->view_right.y::%f) - player->normal_right::%f\n",\
	bsp->node_form->vertex.x2, bsp->node_form->vertex.y2, player->view_right.x, player->view_right.y, player->normal_right);
	is_right_a = dot_prod(bsp->node_form->vertex.x1, bsp->node_form->vertex.y1, player->view_right.x, player->view_right.y) - player->normal_right;
	is_right_b = dot_prod(bsp->node_form->vertex.x2, bsp->node_form->vertex.y2, player->view_right.x, player->view_right.y) - player->normal_right;
	printf("is_right_a::%f=============is_right_b::%f\n", is_right_a, is_right_b);
	printf("P_X::%f\nP_Y::%f\n", player->x, player->y);
	vect_a = normalizing(bsp->node_form->vertex.x1 - player->x, bsp->node_form->vertex.y1 - player->y);
	vect_b = normalizing(bsp->node_form->vertex.x2 - player->x, bsp->node_form->vertex.y2 - player->y);
	angle_a = dot_prod(vect_a.x, vect_a.y, player->view.x, player->view.y);
	angle_b = dot_prod(vect_b.x, vect_b.y, player->view.x, player->view.y);
	angle_a = acos_degree(angle_a);
	angle_b = acos_degree(angle_b);
	if (angle_a >= 90 && angle_b >= 90)
		return ;
	else if (is_right_a >= 0 && is_right_b >= 0 && angle_a > 30 && angle_b > 30)
		return ;
	else if (is_right_a <= 0 && is_right_b <= 0 && angle_a > 30 && angle_b > 30)
		return ;
	else if (is_right_a >= 0 && is_right_b >= 0)
	{
		printf("angle_a:%f\n, angle_b:%f\n", angle_a, angle_b);
		angle_a = angle_a * player->angle_coef;
		angle_b = angle_b * player->angle_coef;
		printf("angle_a:%f\n, angle_b:%f\n", angle_a, angle_b);
		renderer_right(bsp->node_form, player, ft_min_d(angle_a, angle_b), ft_max_d(angle_a, angle_b), doom);
	}
	else if (is_right_a <= 0 && is_right_b <= 0)
	{
		printf("angle_a:%f\n, angle_b:%f\n", angle_a, angle_b);
		angle_a = angle_a * player->angle_coef;
		angle_b = angle_b * player->angle_coef;
		printf("angle_a:%f\n, angle_b:%f\n", angle_a, angle_b);
		renderer_left(bsp->node_form, player, ft_max_d(angle_a, angle_b), ft_min_d(angle_a, angle_b), doom);
	}
	else
	{
		printf("angle_a:%f\n, angle_b:%f\n", angle_a, angle_b);		
		angle_a = angle_a * player->angle_coef;
		angle_b = angle_b * player->angle_coef;
		printf("angle_a:%f\n, angle_b:%f\n", angle_a, angle_b);
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
	printf("DRAW:%c\n", bsp->node_form->n);		
draw_polygon(bsp, player, doom);
printf("\n\n");
	// printf("DRAW:%c\n", bsp->node_form->n);
		recursive_draw(bsp->front, player, doom);
	}
	else
	{
		recursive_draw(bsp->front, player, doom);
	printf("DRAW:%c\n", bsp->node_form->n);
draw_polygon(bsp, player, doom);
printf("\n\n");
	// printf("DRAW:%c\n", bsp->node_form->n);
		recursive_draw(bsp->back, player, doom);
	}
}

void	drawing_wall(t_doom *doom)
{
		printf("==================================================================================================\n");	
	printf("\nSTART DRAWING HERER!!!!!!::::::::::::\n");
	recursive_draw(doom->bsp, doom->gg, doom);
	// printf("PLAYER ON::%c<<<---\nin_front??%f<<<---\n", doom->gg->pos->node_form->n, doom->gg->front);
}
