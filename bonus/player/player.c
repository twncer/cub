/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:10:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/02 09:41:36 by yusudemi         ###   ########.fr       */
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
	t_vector	movement;

	player = &g->map.player;
	(void)key;
	if (g->key_list.w)
	{
		movement.x = MOVE_MULT * cos(player->dov) * MOVE_SPEED;
		movement.y = MOVE_MULT * sin(player->dov) * MOVE_SPEED;
	}
	if (g->key_list.s)
	{
		movement.x = -MOVE_MULT * cos(player->dov) * MOVE_SPEED;
		movement.y = -MOVE_MULT * sin(player->dov) * MOVE_SPEED;
	}
	if (g->key_list.d)
	{
		movement.x = MOVE_MULT * cos(player->dov + (M_PI / 2)) * MOVE_SPEED;
		movement.y = MOVE_MULT * sin(player->dov + (M_PI / 2)) * MOVE_SPEED;
	}
	if (g->key_list.a)
	{
		movement.x = MOVE_MULT * cos(player->dov - (M_PI / 2)) * MOVE_SPEED;
		movement.y = MOVE_MULT * sin(player->dov - (M_PI / 2)) * MOVE_SPEED;
	}
	movement = check_collision(g, movement);
	player->pos.x += movement.x;
	player->pos.y += movement.y;
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
