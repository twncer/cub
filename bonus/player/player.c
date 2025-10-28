/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:10:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/28 00:27:59 by btuncer          ###   ########.fr       */
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
	if (g->key_list.w)
	{
		player->pos.x += 0.05 * cos(player->dov) * MOVE_SPEED;
		player->pos.y += 0.05 * sin(player->dov) * MOVE_SPEED;
	}
	if (g->key_list.s)
	{
		player->pos.x -= 0.05 * cos(player->dov) * MOVE_SPEED;
		player->pos.y -= 0.05 * sin(player->dov) * MOVE_SPEED;
	}
	if (g->key_list.d)
	{
		player->pos.x += 0.05 * cos(player->dov + (M_PI / 2)) * MOVE_SPEED;
		player->pos.y += 0.05 * sin(player->dov + (M_PI / 2)) * MOVE_SPEED;
	}
	if (g->key_list.a)
	{
		player->pos.x += 0.05 * cos(player->dov - (M_PI / 2)) * MOVE_SPEED;
		player->pos.y += 0.05 * sin(player->dov - (M_PI / 2)) * MOVE_SPEED;
	}
	raycasting(g); // raycast only if player moving
}

void	change_direction(t_main *g, int key)
{
	t_player	*player;
	double		rotation_step;

	player = &g->map.player;
	(void)key;
	rotation_step = (FOV * M_PI / 180.0) * SENSITIVITY * 0.05;
	// this means one package goes dont touch this !!
	if (g->key_list.arrow_r)
	{
		player->dov += rotation_step;
		if (player->dov >= (M_PI * 2))
		 	player->dov -= (M_PI * 2);
		list_pop_left(&g->rays);
		raycasting_right_rotation(g);
	}
	if (g->key_list.arrow_l)
	{
		player->dov -= rotation_step;
		if (player->dov < 0)
			player->dov += (2 * M_PI);
		list_pop_right(&g->rays);
		raycasting_left_rotation(g);
	}
}

void	change_direction_advanced(t_main *g, int direction, int weight)
{
	t_player	*player;
	double		rotation_step;

	player = &g->map.player;
	if (weight < 0)
		weight = -weight;
	rotation_step = (((FOV * M_PI / 180.0) * SENSITIVITY) + weight * 0.015) * 0.05;
	// this means one package goes dont touch this !!
	if (direction == 'R')
	{
		player->dov += rotation_step;
		if (player->dov >= (M_PI * 2))
		 	player->dov -= (M_PI * 2);
		list_pop_left(&g->rays);
		raycasting_right_rotation(g);
	}
	if (direction == 'L')
	{
		player->dov -= rotation_step;
		if (player->dov < 0)
			player->dov += (2 * M_PI);
		list_pop_right(&g->rays);
		raycasting_left_rotation(g);
	}
}
