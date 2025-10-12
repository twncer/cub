/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:10:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/12 08:14:34 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include "main.h"
#include <X11/keysym.h>
#include <math.h>

#include <stdio.h>
void	change_position(t_main *g, int key)
{
	t_player	*player;

	player = &g->map.player;
	if (key == XK_w)
	{
		player->pos.x += 0.05 * cos(player->dov) * MOVE_SPEED;
		player->pos.y += 0.05 * sin(player->dov) * MOVE_SPEED;
	}
	else if (key == XK_s)
	{
		player->pos.x -= 0.05 * cos(player->dov) * MOVE_SPEED;
		player->pos.y -= 0.05 * sin(player->dov) * MOVE_SPEED;
	}
	else if (key == XK_d)
	{
		player->pos.x += 0.05 * cos(player->dov + (M_PI / 2)) * MOVE_SPEED;
		player->pos.y += 0.05 * sin(player->dov + (M_PI / 2)) * MOVE_SPEED;
	}
	else // (key == XK_a)
	{
		player->pos.x += 0.05 * cos(player->dov - (M_PI / 2)) * MOVE_SPEED;
		player->pos.y += 0.05 * sin(player->dov - (M_PI / 2)) * MOVE_SPEED;
	}
	cub_render(g, raycasting);
}

void	change_direction(t_main *g, int key)
{
	t_player	*player;
	double		rotation_step;

	player = &g->map.player;
	rotation_step = (FOV * M_PI / 180.0) * SENSITIVITY * 0.05;
	// this means one package goes dont touch this !!
	if (key == XK_Right)
	{
		player->dov += rotation_step;
		if (player->dov >= (M_PI * 2))
		 	player->dov -= (M_PI * 2);
		cub_render(g, raycasting_right_rotation);
	}
	else // (key == XK_Left)
	{
		player->dov -= rotation_step;
		if (player->dov < 0)
			player->dov += (2 * M_PI);
		cub_render(g, raycasting_left_rotation);
	}
}
