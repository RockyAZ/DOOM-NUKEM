/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   228.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 20:26:20 by azaporoz          #+#    #+#             */
/*   Updated: 2018/09/06 18:04:24 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// double	acos_degree(double c)
// {
// 	return (acos(c) * 180 / M_PI);
// }

// int main()
// {
//     // double start = 886;
//     // double end = 295;
//     // double var = start - end;
//     double start = -79;
//     double end = 778;
//     double var = 857;
//     var /= 250;
//     printf("========%f\n", var);
//     for (int i = 0; i <= 250; i++)
//     {
//         printf("%f\n", start);
//         start -= var;
//     }
//     return (0);
// }

int *string()
{
    int i[3] = {1, 2, 3};
    return (&i[1]);
}

int main()
{
    int str2 = *string();

    printf("%d\n", str2);
    return (0);
}
