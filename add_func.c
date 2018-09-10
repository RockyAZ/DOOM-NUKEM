/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 13:40:41 by azaporoz          #+#    #+#             */
/*   Updated: 2018/09/10 13:40:42 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
//DEFINE THIS
double	ft_min_d(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double	ft_max_d(double x, double y)
{
	if (x > y)
		return (x);
	return (y);
}
