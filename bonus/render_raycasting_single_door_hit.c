/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting_single_door_hit.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:46:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/25 23:07:37 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

#include <stdio.h>

t_door_wall	*find_door(int x, int y, t_door_wall *new);
// for now dont think about the door just render a wall that have hole 
// render this -> 0.35(wall) 0.3(hole) 0.35(wall)
// check its axis and calculate its hole?
// if ray pass throug the hole return (0) -> this ray continues its journey
// check the position on the wall that rays hits
// need to find the ray hit point and its side

static int	check_inner_wall_hit(t_cast_data *d, t_door_wall *door)
{
	if (check_intersection(d, door->inner_wall_1))
	{
		if (door->axis == 1)
			d->ray->side = 'W';
		else
			d->ray->side = 'N';
		return (1);
	}
	if (check_intersection(d, door->inner_wall_2))
	{
		if (door->axis == 1) 
			d->ray->side = 'E';
		else
			d->ray->side = 'S';
		return (1);
	}
	return 0;
}

static int	check_door_hit(t_cast_data *d, t_door_wall *door)
{
	if (door->angle >= 89.0)
		return (0);

	if (check_intersection(d, door->pos))
	{
		// need a fucking door texture here
		return (1);
	}
	return (0);
}

static int	insert_inner_wall_hit(t_cast_data *d, t_door_wall *door)
{
    double  wall_hit_pos;

	if (door->axis == 0)
		wall_hit_pos = d->ray->hit.y - floor(d->ray->hit.y);
	else
		wall_hit_pos = d->ray->hit.x - floor(d->ray->hit.x);
	if (wall_hit_pos > 0.35 && wall_hit_pos < 0.65)
	{
		if (check_door_hit(d, door))
			return (1);
		if (check_inner_wall_hit(d, door))
			return (1);
		return (0);
	}
	return (1);
}

int	insert_door_hit(t_cast_data *d, int loc)
{
    t_door_wall	*door;
	int			side;

	door = NULL;
	if (loc)
	{
		door = find_door((int)d->player->pos.x, (int)d->player->pos.y, NULL);
		if (check_door_hit(d, door))
			return (1);
		if (check_inner_wall_hit(d, door))
			return (1);
	}
	else
	{
		door = find_door(d->map_pos.x, d->map_pos.y, NULL);
		side = d->ray->side;
		if (side == 0)
			insert_horizontal_hit(d);
		else
			insert_vertical_hit(d);
		if (side == door->axis)
			return (insert_inner_wall_hit(d, door));
		return (1);
	}
	return (0);
}
