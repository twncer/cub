/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_single.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:50:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 10:55:29 by yusudemi         ###   ########.fr       */
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
// check side
//static int insert_door_hit(t_cast_data *d)
//{
//	t_door	*door;
//	
//	door = find_door(d->map_pos.x, d->map_pos.y, NULL);
//	printf("doorx-y[%d,%d]\ndoorax::%d\n", door->pos.x, door->pos.y, door->axis);
//	if (d->ray->side == 0) // horizontal hit
//	{
//		if (door->axis == 0) // horizontal hole
//		{
//			insert_horizontal_hit(d);
//			// hole here
//			printf("hitx::%f\nhity::%f\n",d->ray->hit.x, d->ray->hit.y);
//			// check the hit position
//			// if hit position on the wall check if ray hits inside of the wall?
//			//
//			return (1);
//		}
//		else // door->axis == 1 vertical hole
//		{
//			insert_horizontal_hit(d);
//			return 1;
//		}
//	}
//	else // d->ray->side == 0) vertical hit
//	{
//		if (door->axis == 0) // horizontal hole
//		{
//			insert_vertical_hit(d);
//			return 1;
//		}
//		else // door->axis == 1 vertical hole
//		{
//			return (0);
//		}
//	}
//	return (0);
//}

static int insert_door_hit(t_cast_data *d)
{
    t_door	*door;
    double	hole_start = 0.35;
    double	hole_end = 0.65;
    double	hit_position;
    
    door = find_door(d->map_pos.x, d->map_pos.y, NULL);
    printf("doorx-y[%d,%d]\ndoorax::%d\n", door->pos.x, door->pos.y, door->axis);
    
    if (d->ray->side == 0) // horizontal hit (hitting east/west wall)
    {
        if (door->axis == 0) // horizontal hole
        {
            insert_horizontal_hit(d);
            printf("hitx::%f\nhity::%f\n", d->ray->hit.x, d->ray->hit.y);
            
            // Calculate where on the wall we hit (0.0 to 1.0)
            hit_position = d->ray->hit.y - floor(d->ray->hit.y);
            printf("hit_position: %f\n", hit_position);
            
            // Check if ray hits the hole part
            if (hit_position >= hole_start && hit_position <= hole_end)
            {
                printf("Ray enters hole, checking internal walls...\n");
                
                // Ray enters the hole - now check if it hits internal walls
                // Calculate where the ray would exit this cell
                double exit_x, exit_y;
                
                if (d->ray_d.x > 0) // ray going east
                {
                    exit_x = d->map_pos.x + 1.0;
                    exit_y = d->player->pos.y + (exit_x - d->player->pos.x) / d->ray_d.x * d->ray_d.y;
                }
                else // ray going west
                {
                    exit_x = d->map_pos.x;
                    exit_y = d->player->pos.y + (exit_x - d->player->pos.x) / d->ray_d.x * d->ray_d.y;
                }
                
                double exit_position = exit_y - floor(exit_y);
                printf("exit_position: %f\n", exit_position);
                
                // Check if ray hits internal walls (top or bottom of hole)
                if (exit_position < hole_start) // hits top internal wall
                {
                    // Calculate exact hit point on top internal wall
                    double internal_y = d->map_pos.y + hole_start;
                    double internal_x = d->player->pos.x + (internal_y - d->player->pos.y) / d->ray_d.y * d->ray_d.x;
                    
                    d->ray->hit.x = internal_x;
                    d->ray->hit.y = internal_y;
                    d->ray->distance = sqrt(pow(internal_x - d->player->pos.x, 2) + 
                                           pow(internal_y - d->player->pos.y, 2));
                    d->ray->side = 'S'; // internal horizontal wall
                    printf("Hit top internal wall\n");
                    return (1);
                }
                else if (exit_position > hole_end) // hits bottom internal wall
                {
                    // Calculate exact hit point on bottom internal wall
                    double internal_y = d->map_pos.y + hole_end;
                    double internal_x = d->player->pos.x + (internal_y - d->player->pos.y) / d->ray_d.y * d->ray_d.x;
                    
                    d->ray->hit.x = internal_x;
                    d->ray->hit.y = internal_y;
                    d->ray->distance = sqrt(pow(internal_x - d->player->pos.x, 2) + 
                                           pow(internal_y - d->player->pos.y, 2));
                    d->ray->side = 'N'; // internal horizontal wall
                    printf("Hit bottom internal wall\n");
                    return (1);
                }
                
                printf("Ray passes through hole completely\n");
                return (0); // Ray passes through hole, continue raycast
            }
            else
            {
                printf("Hit outer wall part\n");
                return (1); // Hit the wall part (not hole)
            }
        }
        else // door->axis == 1 vertical hole (no hole on this side)
        {
            insert_horizontal_hit(d);
            return (1);
        }
    }
    else // d->ray->side == 1 (vertical hit - hitting north/south wall)
    {
        if (door->axis == 0) // horizontal hole (no hole on this side)
        {
            insert_vertical_hit(d);
            return (1);
        }
        else // door->axis == 1 vertical hole
        {
            insert_vertical_hit(d);
            printf("hitx::%f\nhity::%f\n", d->ray->hit.x, d->ray->hit.y);
            
            // Calculate where on the wall we hit (0.0 to 1.0)
            hit_position = d->ray->hit.x - floor(d->ray->hit.x);
            printf("hit_position: %f\n", hit_position);
            
            // Check if ray hits the hole part
            if (hit_position >= hole_start && hit_position <= hole_end)
            {
                printf("Ray enters vertical hole, checking internal walls...\n");
                
                // Calculate where the ray would exit this cell
                double exit_x, exit_y;
                
                if (d->ray_d.y > 0) // ray going south
                {
                    exit_y = d->map_pos.y + 1.0;
                    exit_x = d->player->pos.x + (exit_y - d->player->pos.y) / d->ray_d.y * d->ray_d.x;
                }
                else // ray going north
                {
                    exit_y = d->map_pos.y;
                    exit_x = d->player->pos.x + (exit_y - d->player->pos.y) / d->ray_d.y * d->ray_d.x;
                }
                
                double exit_position = exit_x - floor(exit_x);
                printf("exit_position: %f\n", exit_position);
                
                // Check if ray hits internal walls (left or right of hole)
                if (exit_position < hole_start) // hits left internal wall
                {
                    double internal_x = d->map_pos.x + hole_start;
                    double internal_y = d->player->pos.y + (internal_x - d->player->pos.x) / d->ray_d.x * d->ray_d.y;
                    
                    d->ray->hit.x = internal_x;
                    d->ray->hit.y = internal_y;
                    d->ray->distance = sqrt(pow(internal_x - d->player->pos.x, 2) + 
                                           pow(internal_y - d->player->pos.y, 2));
                    d->ray->side = 'E'; // internal vertical wall
                    printf("Hit left internal wall\n");
                    return (1);
                }
                else if (exit_position > hole_end) // hits right internal wall
                {
                    double internal_x = d->map_pos.x + hole_end;
                    double internal_y = d->player->pos.y + (internal_x - d->player->pos.x) / d->ray_d.x * d->ray_d.y;
                    
                    d->ray->hit.x = internal_x;
                    d->ray->hit.y = internal_y;
                    d->ray->distance = sqrt(pow(internal_x - d->player->pos.x, 2) + 
                                           pow(internal_y - d->player->pos.y, 2));
                    d->ray->side = 'W'; // internal vertical wall
                    printf("Hit right internal wall\n");
                    return (1);
                }
                
                printf("Ray passes through vertical hole completely\n");
                return (0); // Ray passes through hole, continue raycast
            }
            else
            {
                printf("Hit outer wall part\n");
                return (1); // Hit the wall part (not hole)
            }
        }
    }
    return (0);
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
