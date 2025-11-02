/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:47:05 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/31 12:59:19 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// !!!!! this file only include wall collisions. 

// ideas:
// wall collisions -> normal wall - inner wall
// object collisions -> door - fireball(burak?)((make it last))
// need a raycasting like algorithm
// algo:: if player moves and collide to a wall find the hit point
// according to this hit point normalize the walk vector
// if there is no hitting to anywhere just walk

#include "main.h"
#include "doors.h"
#include <math.h>
#include <stdio.h>

static void	find_collision_direction(t_cast_data *d, t_vector pos)
{
	if (d->ray_d.x < 0)
	{
		d->step.x = -1;
		d->side_dist.x = (pos.x - d->map_pos.x) * d->delta_dist.x;
	}
	else if (d->ray_d.x > 0)
	{
		d->step.x = 1;
		d->side_dist.x = (d->map_pos.x + 1.0 - pos.x) * d->delta_dist.x;
	}
	else
	{
		d->step.x = 0;
		d->side_dist.x = 1e30;
	}
	if (d->ray_d.y < 0)
	{
		d->step.y = -1;
		d->side_dist.y = (pos.y - d->map_pos.y) * d->delta_dist.y;
	}
	else if (d->ray_d.y > 0)
	{
		d->step.y = 1;
		d->side_dist.y = (d->map_pos.y + 1.0 - pos.y) * d->delta_dist.y;
	}
	else
	{
		d->step.y = 0;
		d->side_dist.y = 1e30;
	}
}

static void	init_cast_data(t_cast_data *d, t_main *g, double dx, double dy)
{
	d->player = &g->map.player;
	d->map_pos.x = (int)d->player->pos.x;
	d->map_pos.y = (int)d->player->pos.y;
	if (fabs(dx) < 0.0001)
	{
		d->ray_d.x = 0;
		d->delta_dist.x = 1e30;
	}
	else
	{
		d->ray_d.x = (dx > 0) ? 1.0 : -1.0;
		d->delta_dist.x = fabs(1.0 / d->ray_d.x);
	}
	if (fabs(dy) < 0.0001)
	{
		d->ray_d.y = 0;
		d->delta_dist.y = 1e30;
	}
	else
	{
		d->ray_d.y = (dy > 0) ? 1.0 : -1.0;
		d->delta_dist.y = fabs(1.0 / d->ray_d.y);
	}
	find_collision_direction(d, d->player->pos);
}

static double	calculate_wall_distance(t_cast_data *d, t_vector pos, int side)
{
	double	distance;

	if (side == 0)
	{
		distance = (d->map_pos.x - pos.x + ((1 - d->step.x) / 2.0)) / d->ray_d.x;
	}
	else
	{
		distance = (d->map_pos.y - pos.y + ((1 - d->step.y) / 2.0)) / d->ray_d.y;
	}
	return (fabs(distance));
}


static double	check_inner_wall_collision(t_cast_data *d, t_segment wall)
{
	t_vector	wall_d;
	t_vector	ray_d;
	double		det;
	double		dt_wall;
	double		dt_ray;

	wall_d.x = wall.e.x - wall.s.x;
	wall_d.y = wall.e.y - wall.s.y;
	det = d->ray_d.x * wall_d.y - d->ray_d.y * wall_d.x;
	if (fabs(det) < 1e-10)
		return (1000.0);
	ray_d.x = wall.s.x - d->player->pos.x;
	ray_d.y = wall.s.y - d->player->pos.y;
	dt_ray = (ray_d.x * wall_d.y - ray_d.y * wall_d.x) / det;
	dt_wall = (ray_d.x * d->ray_d.y - ray_d.y * d->ray_d.x) / det;
	if (dt_ray > 0 && dt_wall >= 0.0 && dt_wall <= 1.0)
		return (dt_ray);
	return (1000.0);
}

static int	check_door_passage(t_cast_data *d, t_vector pos, t_door_wall *door, int side)
{
	t_vector	hit;
	double		wall_hit_pos;
	double		door_start;
	double		inner_dist;

	if (side != door->axis)
		return (1);
	if (side == 0)
	{
		hit.x = d->map_pos.x + ((1 - d->step.x) / 2.0);
		hit.y = pos.y + ((hit.x - pos.x) / d->ray_d.x) * d->ray_d.y;
		wall_hit_pos = hit.y - floor(hit.y);
	}
	else
	{
		hit.y = d->map_pos.y + ((1 - d->step.y) / 2.0);
		hit.x = pos.x + ((hit.y - pos.y) / d->ray_d.y) * d->ray_d.x;
		wall_hit_pos = hit.x - floor(hit.x);
	}
	door_start = (1.0 - DOOR_WIDTH + PLAYER_RADIUS) / 2.0;
	if (wall_hit_pos > door_start && wall_hit_pos < door_start + DOOR_WIDTH - PLAYER_RADIUS)
		return (1);
	return (0);
}

static double	collision_loop(t_cast_data *d, t_vector pos, char **map, double max_dist)
{
	int			side;
	double		current_dist;
	t_door_wall	*door;

	while (42)
	{
		if (d->side_dist.x < d->side_dist.y)
		{
			d->side_dist.x += d->delta_dist.x;
			d->map_pos.x += d->step.x;
			side = 0;
			current_dist = d->side_dist.x;
		}
		else
		{
			d->side_dist.y += d->delta_dist.y;
			d->map_pos.y += d->step.y;
			side = 1;
			current_dist = d->side_dist.y;
		}
		if (current_dist > max_dist)
			break ;
		if (d->map_pos.y < 0 || !map[d->map_pos.y] ||
			d->map_pos.x < 0 || !map[d->map_pos.y][d->map_pos.x])
			break ;
		if (map[d->map_pos.y][d->map_pos.x] == 'D')
		{
			door = find_door_wall(d->map_pos.x, d->map_pos.y, NULL);
			if (door && !check_door_passage(d, pos, door, side))
				return (calculate_wall_distance(d, pos, side));
		}
		if (map[d->map_pos.y][d->map_pos.x] == '1')
			return (calculate_wall_distance(d, pos, side));
	}
	return (1000.0);
}



static double	check_door_inner_walls(t_cast_data *d, t_door_wall *door)
{
	t_segment	extended_wall1;
	t_segment	extended_wall2;
	t_vector	dir;
	double		len;
	double		wall1_dist;
	double		wall2_dist;

	dir.x = door->inner_wall_1.e.x - door->inner_wall_1.s.x;
	dir.y = door->inner_wall_1.e.y - door->inner_wall_1.s.y;
	len = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= len;
	dir.y /= len;
	extended_wall1.s.x = door->inner_wall_1.s.x - dir.x * (PLAYER_RADIUS / 2);
	extended_wall1.s.y = door->inner_wall_1.s.y - dir.y * (PLAYER_RADIUS / 2);
	extended_wall1.e.x = door->inner_wall_1.e.x + dir.x * (PLAYER_RADIUS / 2);
	extended_wall1.e.y = door->inner_wall_1.e.y + dir.y * (PLAYER_RADIUS / 2);
	dir.x = door->inner_wall_2.e.x - door->inner_wall_2.s.x;
	dir.y = door->inner_wall_2.e.y - door->inner_wall_2.s.y;
	len = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= len;
	dir.y /= len;
	extended_wall2.s.x = door->inner_wall_2.s.x - dir.x * (PLAYER_RADIUS / 2);
	extended_wall2.s.y = door->inner_wall_2.s.y - dir.y * (PLAYER_RADIUS / 2);
	extended_wall2.e.x = door->inner_wall_2.e.x + dir.x * (PLAYER_RADIUS / 2);
	extended_wall2.e.y = door->inner_wall_2.e.y + dir.y * (PLAYER_RADIUS / 2);
	wall1_dist = check_inner_wall_collision(d, extended_wall1);
	wall2_dist = check_inner_wall_collision(d, extended_wall2);
	if (wall1_dist < wall2_dist)
		return (wall1_dist);
	return (wall2_dist);
}

static double	check_current_door(t_cast_data *d, char **map)
{
	t_door_wall	*door;
	double		min_dist;
	double		dist;
	int			px;
	int			py;
	int			dx;
	int			dy;

	px = (int)d->player->pos.x;
	py = (int)d->player->pos.y;
	min_dist = 1000.0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (py + dy >= 0 && map[py + dy] && px + dx >= 0 && 
				map[py + dy][px + dx] == 'D')
			{
				door = find_door_wall(px + dx, py + dy, NULL);
				if (door)
				{
					dist = check_door_inner_walls(d, door);
					if (dist < min_dist)
						min_dist = dist;
				}
			}
			dx++;
		}
		dy++;
	}
	return (min_dist);
}

static double	check_single_axis(t_cast_data *d, t_main *g, double movement)
{
	double	wall_distance;
	double	door_distance;
	double	perp_distance;
	double	min_distance;
	double	max_movement;
	double	movement_sign;
	double	max_check_distance;

	if (fabs(movement) < 0.0001)
		return (0);
	max_check_distance = fabs(movement) + PLAYER_RADIUS + 1.5;
	wall_distance = collision_loop(d, g->map.player.pos, g->map.matrix, max_check_distance);
	door_distance = check_current_door(d, g->map.matrix);
	min_distance = (wall_distance < door_distance) ? wall_distance : door_distance;
	max_movement = min_distance - PLAYER_RADIUS;
	if (max_movement <= 0)
		return (0);
	movement_sign = (movement > 0) ? 1.0 : -1.0;
	if (fabs(movement) <= max_movement)
		return (movement);
	else
		return (max_movement * movement_sign);
}

t_vector	check_collision(t_main *g, t_vector movement)
{
	t_cast_data	d;
	t_vector	ret;

	if (fabs(movement.x) >= 0.0001)
	{
		init_cast_data(&d, g, movement.x, 0);
		ret.x = check_single_axis(&d, g, movement.x);
	}
	else
		ret.x = 0;
	if (fabs(movement.y) >= 0.0001)
	{
		init_cast_data(&d, g, 0, movement.y);
		ret.y = check_single_axis(&d, g, movement.y);
	}
	else
		ret.y = 0;
	return (ret);
}
