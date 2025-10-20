/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_single.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:50:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/20 22:00:11 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

static void	find_ray_direction(t_cast_data *d)
{
	if (d->ray_d.x < 0) // west
	{
		d->step.x = -1;
		d->side_dist.x = (d->player->pos.x - d->map_pos.x)
			* fabs(1.0 / d->ray_d.x);
	}
	else // east
	{
		d->step.x = 1;
		d->side_dist.x = ((d->map_pos.x + 1.0) - d->player->pos.x)
			* fabs(1.0 / d->ray_d.x);
	}
	if (d->ray_d.y < 0) // north
	{
		d->step.y = -1;
		d->side_dist.y = (d->player->pos.y - d->map_pos.y)
			* fabs(1.0 / d->ray_d.y);
	}
	else // south
	{
		d->step.y = 1;
		d->side_dist.y = ((d->map_pos.y + 1.0) - d->player->pos.y)
			* fabs(1.0 / d->ray_d.y);
	}
}

static void	insert_horizontal_hit(t_cast_data *d)
{
	d->ray->distance = (d->map_pos.x - d->player->pos.x +
			((1 - d->step.x) / 2)) / d->ray_d.x;
	if (d->step.x == 1)
	{
		d->ray->side = 'E';
		d->ray->hit.x = d->map_pos.x;
	}
	else
	{
		d->ray->side = 'W';
		d->ray->hit.x = d->map_pos.x + 1.0;
	}
	d->ray->hit.y = d->player->pos.y +
		(d->ray->distance * d->ray_d.y);
}

static void	insert_vertical_hit(t_cast_data *d)
{
	d->ray->distance = (d->map_pos.y - d->player->pos.y +
			((1 - d->step.y) / 2)) / d->ray_d.y;
	if (d->step.y == 1)
	{
		d->ray->side = 'S'; // now im sure xd
		d->ray->hit.y = d->map_pos.y;
	}
	else
	{
		d->ray->side = 'N';
		d->ray->hit.y = d->map_pos.y + 1;
	}
	d->ray->hit.x = d->player->pos.x +
		(d->ray->distance * d->ray_d.x);
}
// for now dont think about the door just render a wall that have hole 
// render this -> 0.35(wall) 0.3(hole) 0.35(wall)
// check its axis and calculate its hole?
// if ray pass throug the hole return (0) -> this ray continues its journey
// check the position on the wall that rays hits
// need to find the ray hit point and its side
t_door	*find_door(int x, int y, t_door *new);
#include <stdio.h>

static int	check_inner_wall_hit(t_cast_data *d, t_door *door) // use 
{
	(void)d;
	(void)door;
	return (0);
}

static int insert_door_hit(t_cast_data *d)
{
    t_door  *door;
    double  wall_hit_pos;
    
    door = find_door(d->map_pos.x, d->map_pos.y, NULL);
    if (d->ray->side == 0) // Horizontal hit
    {
        double hit_y = d->player->pos.y + 
            ((d->map_pos.x - d->player->pos.x + ((1 - d->step.x) / 2)) 
            / d->ray_d.x) * d->ray_d.y;
        wall_hit_pos = hit_y - floor(hit_y);
        if (door->axis == 1)
        {
            if (wall_hit_pos >= 0.35 && wall_hit_pos <= 0.65)
                return (check_inner_wall_hit(d, door));
        }
        insert_horizontal_hit(d);
        return (1);
    }
    else // Vertical hit
    {
        double hit_x = d->player->pos.x + 
            ((d->map_pos.y - d->player->pos.y + ((1 - d->step.y) / 2)) 
            / d->ray_d.y) * d->ray_d.x;
        wall_hit_pos = hit_x - floor(hit_x);
        if (door->axis == 0)
        {
            if (wall_hit_pos >= 0.35 && wall_hit_pos <= 0.65)
                return (check_inner_wall_hit(d, door));
        }
        insert_vertical_hit(d);
        return (1);
    }
}

void	raycast_single(t_cast_data *d, char **matrix)
{
	d->map_pos.x = (int)d->player->pos.x;
	d->map_pos.y = (int)d->player->pos.y;
	find_ray_direction(d);
	while (42)
	{
		if (d->side_dist.x < d->side_dist.y)
		{
			d->side_dist.x += fabs(1.0 / d->ray_d.x);
			d->map_pos.x += d->step.x;
			d->ray->side = 0;
		}
		else
		{
			d->side_dist.y += fabs(1.0 / d->ray_d.y);
			d->map_pos.y += d->step.y;
			d->ray->side = 1;
		}
		// if you looking here and want to delete this just dont xd
		if (d->map_pos.y < 0 || !matrix[d->map_pos.y] || 
			d->map_pos.x < 0 || !matrix[d->map_pos.y][d->map_pos.x])
			break ;
		// in here need to add doors
		if (matrix[d->map_pos.y][d->map_pos.x] == 'D')
			if (insert_door_hit(d))
				return ;
		if (matrix[d->map_pos.y][d->map_pos.x] == '1')
			break ;
	}
	if (d->ray->side == 0)
		insert_horizontal_hit(d);
	else
		insert_vertical_hit(d);
}
