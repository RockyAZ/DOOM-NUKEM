/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 17:12:06 by azaporoz          #+#    #+#             */
/*   Updated: 2018/09/02 17:12:07 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct      s_list
{
	int             x;
	struct s_list   *next;
}                   t_list;

t_list    *push_front(t_list *main, t_list *current)
{
	current->next = main;
	return (current);
}

void	push_back(t_list **sorted, t_list *main)
{
	t_list *p;

	p = *sorted;
	if (*sorted == NULL)
	{
		*sorted = main;

		return ;
	}
	while (p->next != NULL)
		p = p->next;
	p->next = main;
}

t_list **sorted(t_list *main)
{
	int count = 0;
	t_list **res;
	t_list *p;

	res = NULL;
	p = main;
	while (main)
	{
		if (main->x <= 5)
			count++;
		main = main->next;
	}
	res = (t_list**)malloc(sizeof(t_list*) * count);
	int i = 0;
	while (p)
	{
		if (p->x <= 5)
			res[i++] = p;
		p = p->next;
	}
	res[count] = NULL;
	return (res);
}

void	f(t_list *list)
{
	list = (t_list*)malloc(sizeof(t_list));
}

int main()
{
	int i = 0;
	t_list *first;
	t_list *main;

	t_list **sorted_list;

	main = (t_list*)malloc(sizeof(t_list));
	main->x = i;
	first = main;
	while (i++ < 10)
	{
		main->next = (t_list*)malloc(sizeof(t_list));
		main = main->next;
		main->x = i;
	}
	main->next = NULL;
	main = first;


	t_list *demo;
	t_list *tru;

	t_list *fal;
	demo = (t_list*)malloc(sizeof(t_list));
	tru = demo;
	fal = main;
	if (tru == demo)
		printf("tru == demo\n");
	if (fal != demo)
		printf("fal == demo\n");
// sorted_list = sorted(main);
// 	while (main)
// 	{
// 		printf("LIST::%d\n", main->x);
// 		main = main->next;
// 	}
// printf("============\n");
// 	i = 0;
// 	while (sorted_list[i])
// 	{
// 		printf("LIST::%d\n", sorted_list[i]->x);
// 		i++;
// 	}
	return (0);
}

// void RenderBSP(Node *node)
// {
//   int result = ClassifyPoint(camera_position,node->splitter_polygon);

//   if (result == FRONT)
//   {
//     if (node->back != NULL)
// 		RenderBSP(node->back);
//     DrawPolygon(node->splitter_polygon);
//     if (node->front != NULL)
// 		RenderBSP(node->front);
//   }
//   else
//   {
//     if (node->front != NULL) RenderBSP(node->front);
//     DrawPolygon(node->splitter_polygon);
//     if (node->back != NULL) RenderBSP(node->back);
//   }

//   return;
// }
