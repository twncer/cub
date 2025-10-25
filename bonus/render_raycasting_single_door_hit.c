/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting_single_door_hit.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:46:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/24 16:29:16 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

#include <stdio.h>

void	insert_vertical_hit(t_cast_data *d);
void	insert_horizontal_hit(t_cast_data *d);
int	check_inner_wall_hit(t_cast_data *d, t_door_wall *door); // use 
t_door_wall	*find_door(int x, int y, t_door_wall *new);
// for now dont think about the door just render a wall that have hole 
// render this -> 0.35(wall) 0.3(hole) 0.35(wall)
// check its axis and calculate its hole?
// if ray pass throug the hole return (0) -> this ray continues its journey
// check the position on the wall that rays hits
// need to find the ray hit point and its side

static int check_intersection(t_cast_data *d, t_segment inner_wall)
{ // need a struct named door_cast_data
	double wall_dx = inner_wall.e.x - inner_wall.s.x;
	double wall_dy = inner_wall.e.y - inner_wall.s.y;
	double cross = d->ray_d.x * wall_dy - d->ray_d.y * wall_dx;
	if (fabs(cross) < 1e-10)
		return (0);
    
	double to_start_x = inner_wall.s.x - d->player->pos.x;
	double to_start_y = inner_wall.s.y - d->player->pos.y;
	double ray_param = (to_start_x * wall_dy - to_start_y * wall_dx) / cross;
	double wall_param = (to_start_x * d->ray_d.y - to_start_y * d->ray_d.x) / cross;
	if (ray_param > 0 && wall_param >= 0 && wall_param <= 1)
	{
		d->ray->hit.x = d->player->pos.x + ray_param * d->ray_d.x;
		d->ray->hit.y = d->player->pos.y + ray_param * d->ray_d.y;
		d->ray->distance = ray_param;
		return (1);
	}
	return (0);// im the god
}

int	check_inner_wall_hit(t_cast_data *d, t_door_wall *door)
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

// need a fucking refactor after putting the fucking door!!
int insert_door_hit(t_cast_data *d)
{
    t_door_wall  *door;
    double  wall_hit_pos;

	door = find_door(d->map_pos.x, d->map_pos.y, NULL);
	if (d->ray->side == 0) // Horizontal hit
	{
		insert_horizontal_hit(d);
		wall_hit_pos = d->ray->hit.y - floor(d->ray->hit.y);
		//printf("walhitpos::%f\n", wall_hit_pos);
		if (door->axis == 0 && wall_hit_pos > 0.35 && wall_hit_pos < 0.65)
		{
			// check is there a door hit 
			if (check_door_hit(d, door))
				return 1;
			// check inner door hits if there is no door 
			if (check_inner_wall_hit(d, door))
				return 1;
			return 0;
		}
		return (1);
	}
	else // Vertical hit
	{
		insert_vertical_hit(d);
		wall_hit_pos = d->ray->hit.x - (int)(d->ray->hit.x);
		//printf("walhitpos::%f\n", wall_hit_pos);
		if (door->axis == 1 && wall_hit_pos >= 0.35 && wall_hit_pos <= 0.65)
		{
			if (check_door_hit(d, door))
				return 1;
			if (check_inner_wall_hit(d, door))
			{
				return 1;
			}
			// after all if door is closed put door on wall_hit_pos 0.35 0.65 in here
			// make an opening state fck
			return 0;
		}
		return (1);
	}
	return (0);
}
