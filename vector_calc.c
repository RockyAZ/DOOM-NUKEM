/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 11:44:09 by azaporoz          #+#    #+#             */
/*   Updated: 2018/09/04 11:44:09 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	dot_prod(double x1, double y1, double x2, double y2)
{
	return ((x1 * x2) + (y1 * y2));
}

// double	calc_normal(double x1, double y1, double x2, double y2)
// {
// 	double res;

// 	dot_prod
// 	return (res);
// }

// t_vector	calc_normal(t_form *form)
// {
// 	t_vector norm;

// 	norm.x = form->vertex.x2 - form->vertex.x1;
// 	norm.y = form->vertex.y2 - form->vertex.y1;
// 	return (norm);
// }

// void		calc_perpend(t_form *form)
// {
// 	form->perp.x = form->normal.y;
// 	form->perp.y = form->normal.x * -1;
// }

double	pifagor(double a, double b)
{
	double res;

	res = sqrt(powf(a, 2) + powf(b, 2));
	if (res == 0)
		return (1);
	return (res);
}

t_vector normalizing(double x, double y)
{
	t_vector res;
	double len;

	len = pifagor(x, y);
	res.x = x / len;
	res.y = y / len;
	return (res);
}

void	vector_prep(t_form *form)
{
	int		center_x;
	int		center_y;
	// double	len;

	center_x = form->vertex.x2 - form->vertex.x1;
	center_y = form->vertex.y2 - form->vertex.y1;
	center_x ^= center_y;
	center_y ^= center_x;
	center_x ^= center_y;
	center_y *= -1;
// 	len = pifagor(center_x, center_y);
// //???
// 	if (len == 0)
// 		len = 1;
	// form->norm.x = center_x / len;
	// form->norm.y = center_y / len;
	form->norm = normalizing(center_x, center_y);
	form->dist = dot_prod(form->vertex.x1, form->vertex.y1, form->norm.x, form->norm.y);
	form->len = pifagor(form->vertex.x1 - form->vertex.x2, form->vertex.y1 - form->vertex.y2);
	form->center.x = (form->vertex.x1 + form->vertex.x2) >> 1;
	form->center.y = (form->vertex.y1 + form->vertex.y2) >> 1;
}

///////shit!!!
void	print_bsp(t_bsp *bsp)
{
	static int i;
	if (bsp->is_leaf)
	{
		printf("END LINE\n");
		return ;
	}
printf("%d->%c\n", i, bsp->node_form->n);
	i++;
	print_bsp(bsp->front);
	print_bsp(bsp->back);
}
