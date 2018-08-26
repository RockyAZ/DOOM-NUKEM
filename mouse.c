/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:58:37 by azaporoz          #+#    #+#             */
/*   Updated: 2018/08/09 15:58:38 by azaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	mouse_pos(t_main *win)
{
	if (win->e.type == SDL_MOUSEMOTION)
	{
		win->gg.angle -= win->e.motion.xrel * 0.3;
		win->gg.up_down -= win->e.motion.yrel * 0.3;
		if (win->gg.angle >= 360)
			win->gg.angle -= 360;
		if (win->gg.angle < 0)
			win->gg.angle += 360;
		win->m.x = win->e.motion.x;
		win->m.y = win->e.motion.y;
	}
}
