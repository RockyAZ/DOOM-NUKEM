/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:17:48 by azaporoz          #+#    #+#             */
/*   Updated: 2018/09/06 18:17:49 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	ft_tan(double angle)
{
	return (tan((angle * 2 * M_PI) / 360));
}

double	ft_cos(double angle)
{
	return (cos((angle * 2 * M_PI) / 360));
}

double	ft_sin(double angle)
{
	return (sin((angle * 2 * M_PI) / 360));
}

double	acos_degree(double c)
{
	return (acos(c) * 180 / M_PI);
}
