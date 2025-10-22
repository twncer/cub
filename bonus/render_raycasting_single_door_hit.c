/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting_single_door_hit.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:46:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/22 21:16:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

#include <stdio.h>

void	insert_vertical_hit(t_cast_data *d);
void	insert_horizontal_hit(t_cast_data *d);
static int	check_inner_wall_hit(t_cast_data *d, t_door *door); // use 
t_door	*find_door(int x, int y, t_door *new);
// for now dont think about the door just render a wall that have hole 
// render this -> 0.35(wall) 0.3(hole) 0.35(wall)
// check its axis and calculate its hole?
// if ray pass throug the hole return (0) -> this ray continues its journey
// check the position on the wall that rays hits
// need to find the ray hit point and its side
static int	check_intersection(t_cast_data *d, t_segment inner_wall)
{
	int a = d->direction;
	d->direction;
	d->ray->hit.x;
	d->ray->hit.y;
	
	// 
	return(1);
}

static int	check_inner_wall_hit(t_cast_data *d, t_door *door)
{
	double	new_dist;

}


int insert_door_hit(t_cast_data *d)
{
    t_door  *door;
    double  wall_hit_pos;

	door = find_door(d->map_pos.x, d->map_pos.y, NULL);
	if (d->ray->side == 0) // Horizontal hit
	{
		insert_horizontal_hit(d);
		wall_hit_pos = d->ray->hit.y - floor(d->ray->hit.y);
		if (door->axis == 1 && wall_hit_pos >= 0.35 && wall_hit_pos <= 0.65)
	    	return (check_inner_wall_hit(d, door));
		return (1);
	}
	else // Vertical hit
	{
		insert_vertical_hit(d);
		wall_hit_pos = d->ray->hit.x - floor(d->ray->hit.x);
		if (door->axis == 0 && wall_hit_pos >= 0.35 && wall_hit_pos <= 0.65)
			return (check_inner_wall_hit(d, door));
		return (1);
	}
	return (0);
}
