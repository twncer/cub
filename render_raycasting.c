/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:20:16 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/11 19:31:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include "main.h"
#include <math.h>

#include <stdio.h>

void	raycasting(t_main *g)
{
	t_ray_node	*curr;
	int			i;
	t_cast_data	d;

	d.fov_rad = FOV * (M_PI) / 180.0;
	d.direction = g->map.player.dov - (d.fov_rad / 2.0);
	curr = g->rays.head;
	d.player = &g->map.player;
	while (curr)
	{
		i = -1;
		while (++i < g->rays.package_size)
		{
			d.ray = &(curr->ray_pack[i]);
			d.ray_d.x = cos(d.direction);
			d.ray_d.y = sin(d.direction);
			raycast_single(&d, g->map.matrix);
			curr->ray_pack[i].distance *= cos(d.direction - g->map.player.dov);
			d.direction += d.fov_rad / WIN_WIDTH;
		}
		curr = curr->next;
	}
}

void	raycasting_right_rotation(t_main *g)
{
	(void)g;
	// need to render screen_width * sensitivity * 0.05
}

void	raycasting_left_rotation(t_main *g)
{
	(void)g;
}
