/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 19:23:00 by azaporoz          #+#    #+#             */
/*   Updated: 2018/07/23 19:23:00 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

float	ft_tan(float angle)
{
	return (tan((angle * 2 * M_PI) / 360));
}

float	ft_cos(float angle)
{
	return (cos((angle * 2 * M_PI) / 360));
}

float	ft_sin(float angle)
{
	return (sin((angle * 2 * M_PI) / 360));
}

void	ft_arrr_del(char **arr, char *line)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	free(line);
}

int		pifagor(t_main *win, float angle, char c)
{
	if (c == 'v')
	{
		return (((int)sqrt(powf(win->gg.p_x - win->ray.v_dot.pix_x, 2) +\
		powf(win->gg.p_y - win->ray.v_dot.pix_y, 2))) *\
		ft_cos(win->gg.angle - angle));
	}
	else if (c == 'h')
	{
		return (((int)sqrt(powf(win->gg.p_x - win->ray.h_dot.pix_x, 2) +\
		powf(win->gg.p_y - win->ray.h_dot.pix_y, 2))) *\
		ft_cos(win->gg.angle - angle));
	}
	else
		return (0);
}
