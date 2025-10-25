/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/24 04:08:43 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include "main.h"
#include <stddef.h>
#include <math.h>

#include <stdio.h>
t_door_wall	*find_door(int x, int y, t_door_wall *new)
{
	static t_door_wall *doors = NULL;
	static int count = 0;
	int	i;

	if (x == -1 && new)
	{
		count = y;
		doors = new;
		return (NULL);
	}
	i = -1;
	while (++i < count)
	{
		if (x == doors[i].map_pos.x && y == doors[i].map_pos.y)
			return (&doors[i]);
	}
	return (NULL);
}

// interact_door
void	interact_door(t_door_wall *door)
{
	if (door->state == LOCKED || door->state == BURNING || door->state == DESTROYED)
		return ;
	if (door->angle < M_PI / 4.0) // open door if angle < 45 degrees
	{
		door->target_angle = M_PI / 2.0;
		door->state = OPENING;
	}
	else // close door
	{
		door->target_angle = 0.0;
		door->state = CLOSING;
	}
}
// this func gonna rotate the door until it reach the target_angle .p
void	rotate_door(t_door_wall *door)
{
	double	next_angle;
	double	hop;

	if (door->angle == door->target_angle)
		return ;
	hop = (M_PI / 360.0) * DOOR_SPEED;

	next_angle = door->angle + hop;
	
	if (fabs(door->target_angle - next_angle) > hop)
		door->angle = door->target_angle;
	else
	{
		
	}
}
