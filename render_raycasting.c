/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:20:16 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 05:14:33 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include "main.h"
#include <math.h>

#include <stdio.h>

void	raycasting(t_main *g)
{
	t_ray_node	*curr;
	int			x;
	double		fov_rad;
	double		direction;
	t_cast_data	d;

	fov_rad = FOV * (M_PI) / 180.0;
	direction = g->map.player.dov - (fov_rad / 2.0);
	curr = g->rays.head;
	x = -1;
	d.player = &g->map.player;
	while (++x < WIN_WIDTH && curr)
	{
		d.ray = &curr->ray;
		d.ray_d.x = cos(direction);
		d.ray_d.y = sin(direction);
		printf("fuc\n");
		raycast_single(&d, g->map.matrix);
		printf("fuc2\n");
		curr->ray.distance *= cos(direction - g->map.player.dov);
		direction += fov_rad / WIN_WIDTH;
		curr = curr->next;
	}
	printf("fuc3\n");
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
