/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:58:28 by azaporoz          #+#    #+#             */
/*   Updated: 2018/09/02 15:58:28 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	sort_form(t_bsp *bsp)
{
	int i;
	int dot_neg;
	int dot_pos;
	t_form *first;

	i = 0;
	dot_neg = 0;
	dot_pos = 0;
	while (bsp->arr_form[i] != NULL)
	{
		if (bsp->arr_form[i] != bsp->node_form && dot_prod(bsp->node_form->norm.x, bsp->node_form->norm.y, bsp->arr_form[i]->vertex.x1, bsp->arr_form[i]->vertex.y1) - bsp->node_form->dist > 0)
			dot_pos++;
		else if (bsp->arr_form[i] != bsp->node_form)
			dot_neg++;
		i++;
	}
	bsp->front->arr_form = (t_form**)malloc(sizeof(t_form*) * (dot_pos + 1));
	bsp->back->arr_form = (t_form**)malloc(sizeof(t_form*) * (dot_neg + 1));
	i = 0;
	dot_pos = 0;
	dot_neg = 0;
	while (bsp->arr_form[i] != NULL)
	{
		if (bsp->arr_form[i] != bsp->node_form && dot_prod(bsp->node_form->norm.x, bsp->node_form->norm.y, bsp->arr_form[i]->vertex.x1, bsp->arr_form[i]->vertex.y1) - bsp->node_form->dist > 0)
		{
			bsp->front->arr_form[dot_pos] = bsp->arr_form[i];
			dot_pos++;
		}
		else if (bsp->arr_form[i] != bsp->node_form)
		{
			bsp->back->arr_form[dot_neg] = bsp->arr_form[i];
			dot_neg++;
		}
		i++;
	}
	bsp->front->arr_form[dot_pos] = NULL;
	bsp->back->arr_form[dot_neg] = NULL;
	i = 0;
	while (bsp->front->arr_form[i] != NULL)
	{
		printf("front:%d:%c\n", i, bsp->front->arr_form[i]->n);
		i++;
	}
	i = 0;
	while (bsp->back->arr_form[i] != NULL)
	{
		printf("back:%d:%c\n", i, bsp->back->arr_form[i]->n);
		i++;
	}
}

void		make_bsp(t_bsp **bsp)
{
	static int	first;
	t_bsp		*p;

	p = *bsp;
	printf("---->>>>VAR:::%d<<<<----\n", first);
	if (p->arr_form[0] == NULL)
	{
		p->node_form = NULL;
		p->is_leaf = 1;
		p->is_solid = 1;
		return ;
	}
	if (first != 0)
		p->node_form = p->arr_form[0];
	first++;
	p->front = (t_bsp*)malloc(sizeof(t_bsp));
	p->back = (t_bsp*)malloc(sizeof(t_bsp));
	sort_form(*bsp);
	p->is_leaf = 0;
	p->is_solid = 0;
	make_bsp(&p->back);
	make_bsp(&p->front);
}

void	first_bsp(t_doom *doom)
{
	int		i;
	t_bsp	*bsp;
	t_form	*first_form;

	i = 0;
	first_form = doom->first_form;
	bsp = (t_bsp*)malloc(sizeof(t_bsp));
	bsp->node_form = doom->first_form;
	bsp->arr_form = (t_form**)malloc(sizeof(t_form*) * (doom->form_counter + 1));
	while (i < doom->form_counter)
	{
		bsp->arr_form[i] = doom->first_form;
		doom->first_form = doom->first_form->next;
		i++;
	}
	doom->first_form = first_form;
	bsp->arr_form[i] = NULL;
	make_bsp(&bsp);
	doom->bsp = bsp;
}
