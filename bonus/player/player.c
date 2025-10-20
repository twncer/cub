/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:10:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/20 21:56:12 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include "../main/main.h"
#include <X11/keysym.h>
#include <math.h>

#include <stdio.h>
void	change_position(t_main *g, int key)
{
	t_player	*player;

	player = &g->map.player;
	(void)key;
	if (g->key_list.W)
	{
		player->pos.x += 0.05 * cos(player->dov) * MOVE_SPEED;
		player->pos.y += 0.05 * sin(player->dov) * MOVE_SPEED;
	}
	if (g->key_list.S)
	{
		player->pos.x -= 0.05 * cos(player->dov) * MOVE_SPEED;
		player->pos.y -= 0.05 * sin(player->dov) * MOVE_SPEED;
	}
	if (g->key_list.D)
	{
		player->pos.x += 0.05 * cos(player->dov + (M_PI / 2)) * MOVE_SPEED;
		player->pos.y += 0.05 * sin(player->dov + (M_PI / 2)) * MOVE_SPEED;
	}
	if (g->key_list.A)
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
		list_pop_left(&g->rays);
		cub_render(g, raycasting_right_rotation);
	}
	else // (key == XK_Left)
	{
		player->dov -= rotation_step;
		if (player->dov < 0)
			player->dov += (2 * M_PI);
		list_pop_right(&g->rays);
		cub_render(g, raycasting_left_rotation);
	}
}
