/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:10:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/31 12:55:27 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include "main.h"
#include <X11/keysym.h>
#include <math.h>

#include <stdio.h>

// on wall collision checking check x and y axis seperatly 
// if x-y axis on wall find closest positon to the wall and move player to this loc
// after finding the closest position find a new move_speed for y to normalize walking
// if closest position is player position for x and y player stops
// if closest position is player position for x and y can stil can go further moves on y direction slowly (on minimum move_speed maybe?)
// you have tons of ray data check the fuckn distance 
// if distance is too low so just dont fucking move there

t_vector	check_collision(t_main *g, t_vector movement);

void	change_position(t_main *g, int key)
{
	t_player	*player;
	t_vector	movement;

	player = &g->map.player;
	if (key == XK_w)
	{
		movement.x = 0.05 * cos(player->dov) * MOVE_SPEED;
		movement.y = 0.05 * sin(player->dov) * MOVE_SPEED;
	}
	else if (key == XK_s)
	{
		movement.x = -0.05 * cos(player->dov) * MOVE_SPEED;
		movement.y = -0.05 * sin(player->dov) * MOVE_SPEED;
	}
	else if (key == XK_d)
	{
		movement.x = 0.05 * cos(player->dov + (M_PI / 2)) * MOVE_SPEED;
		movement.y = 0.05 * sin(player->dov + (M_PI / 2)) * MOVE_SPEED;
	}
	else // (key == XK_a)
	{
		movement.x = 0.05 * cos(player->dov - (M_PI / 2)) * MOVE_SPEED;
		movement.y = 0.05 * sin(player->dov - (M_PI / 2)) * MOVE_SPEED;
	}
	movement = check_collision(g, movement);
	player->pos.x += movement.x;
	player->pos.y += movement.y;
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
