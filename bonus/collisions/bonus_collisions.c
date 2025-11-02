/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:47:05 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/02 09:32:34 by yusudemi         ###   ########.fr       */
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

#include "../main/main.h"
#include <math.h>
#include <stdio.h>

static void	init_axis_direction(double ray_dir, double pos, double map_pos,
				double delta, int *step, double *side_dist)
{
	if (ray_dir < 0)
	{
		*step = -1;
		*side_dist = (pos - map_pos) * delta;
	}
	else if (ray_dir > 0)
	{
		*step = 1;
		*side_dist = (map_pos + 1.0 - pos) * delta;
	}
	else
	{
		*step = 0;
		*side_dist = INFINITY_DISTANCE;
	}
}

static void	init_ray_axis(double delta, double *ray_dir, double *delta_dist)
{
	if (fabs(delta) < 0.0001)
	{
		*ray_dir = 0;
		*delta_dist = INFINITY_DISTANCE;
	}
	else
	{
		if (delta > 0)
			*ray_dir = 1.0;
		else
			*ray_dir = -1.0;
		*delta_dist = fabs(1.0 / *ray_dir);
	}
}

static void	init_cast_data(t_cast_data *d, t_main *g, double dx, double dy)
{
	d->player = &g->map.player;
	d->map_pos.x = (int)d->player->pos.x;
	d->map_pos.y = (int)d->player->pos.y;
	init_ray_axis(dx, &d->ray_d.x, &d->delta_dist.x);
	init_ray_axis(dy, &d->ray_d.y, &d->delta_dist.y);
	init_axis_direction(d->ray_d.x, d->player->pos.x, d->map_pos.x,
		d->delta_dist.x, &d->step.x, &d->side_dist.x);
	init_axis_direction(d->ray_d.y, d->player->pos.y, d->map_pos.y,
		d->delta_dist.y, &d->step.y, &d->side_dist.y);
}

static double	calculate_wall_distance(t_cast_data *d, t_vector pos, int side)
{
	double	distance;

	if (side == 0)
		distance = (d->map_pos.x - pos.x + ((1 - d->step.x) / 2.0)) / d->ray_d.x;
	else
		distance = (d->map_pos.y - pos.y + ((1 - d->step.y) / 2.0)) / d->ray_d.y;
	return (fabs(distance));
}


static double	find_collision_distance(t_cast_data *d, t_segment wall)
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

static double	calculate_hit_position(t_cast_data *d, t_vector pos, int side)
{
	t_vector	hit;

	if (side == 0)
	{
		hit.x = d->map_pos.x + ((1 - d->step.x) / 2.0);
		hit.y = pos.y + ((hit.x - pos.x) / d->ray_d.x) * d->ray_d.y;
		return (hit.y - floor(hit.y));
	}
	else
	{
		hit.y = d->map_pos.y + ((1 - d->step.y) / 2.0);
		hit.x = pos.x + ((hit.y - pos.y) / d->ray_d.y) * d->ray_d.x;
		return (hit.x - floor(hit.x));
	}
}

static int	check_doorwall_passage(t_cast_data *d, t_vector pos, t_door_wall *dw, int side)
{
	double	wall_hit_pos;
	double	door_start;
	double	door_end;

	if (side != dw->axis)
		return (1);
	wall_hit_pos = calculate_hit_position(d, pos, side);
	door_start = (1.0 - DOOR_WIDTH + PLAYER_RADIUS) / 2.0;
	door_end = door_start + DOOR_WIDTH - PLAYER_RADIUS;
	if (wall_hit_pos > door_start && wall_hit_pos < door_end)
		return (1);
	return (0);
}

static void	step_ray(t_cast_data *d, int *side, double *dist)
{
	if (d->side_dist.x < d->side_dist.y)
	{
		d->side_dist.x += d->delta_dist.x;
		d->map_pos.x += d->step.x;
		*side = 0;
		*dist = d->side_dist.x;
	}
	else
	{
		d->side_dist.y += d->delta_dist.y;
		d->map_pos.y += d->step.y;
		*side = 1;
		*dist = d->side_dist.y;
	}
}

static double	check_wall_collision(t_cast_data *d, t_vector pos, char **map, double max_dist)
{
	int			side;
	double		dist;
	t_door_wall	*dw;

	while (1)
	{
		step_ray(d, &side, &dist);
		if (dist > max_dist)
			break ;
		if (d->map_pos.y < 0 || !map[d->map_pos.y] ||
			d->map_pos.x < 0 || !map[d->map_pos.y][d->map_pos.x])
			break ;
		if (map[d->map_pos.y][d->map_pos.x] == 'D')
		{
			dw = find_door_wall(d->map_pos.x, d->map_pos.y, NULL);
			if (dw && !check_doorwall_passage(d, pos, dw, side))
				return (calculate_wall_distance(d, pos, side));
		}
		if (map[d->map_pos.y][d->map_pos.x] == '1')
			return (calculate_wall_distance(d, pos, side));
	}
	return (1000.0);
}

static t_segment	extend_segment(t_segment seg, double extension)
{
	t_vector	dir;
	double		len;
	t_segment	result;

	dir.x = seg.e.x - seg.s.x;
	dir.y = seg.e.y - seg.s.y;
	len = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= len;
	dir.y /= len;
	result.s.x = seg.s.x - dir.x * extension;
	result.s.y = seg.s.y - dir.y * extension;
	result.e.x = seg.e.x + dir.x * extension;
	result.e.y = seg.e.y + dir.y * extension;
	return (result);
}

static double	check_doorwall_inner_walls(t_cast_data *d, t_door_wall *dw)
{
	t_segment	wall;
	double		dist1;
	double		dist2;

	wall = extend_segment(dw->inner_wall_1, PLAYER_RADIUS / 2);
	dist1 = find_collision_distance(d, wall);
	wall = extend_segment(dw->inner_wall_2, PLAYER_RADIUS / 2);
	dist2 = find_collision_distance(d, wall);
	if (dist1 < dist2)
		return (dist1);
	return (dist2);
}

static double	check_doorwall_collision(t_cast_data *d, char **map)
{
	t_door_wall	*dw;
	double		min_dist;
	double		dist;
	int			x;
	int			y;

	min_dist = 1000.0;
	y = (int)d->player->pos.y - 1 - 1;
	while (++y <= (int)d->player->pos.y + 1)
	{
		x = (int)d->player->pos.x - 1 - 1;
		while (++x <= (int)d->player->pos.x + 1)
		{
			if (y >= 0 && map[y] && x >= 0 && map[y][x] == 'D')
			{
				dw = find_door_wall(x, y, NULL);
				if (!dw)
					continue ;
				dist = check_doorwall_inner_walls(d, dw);
				if (dist < min_dist)
					min_dist = dist;
			}
		}
	}
	return (min_dist);
}

static double	check_object_collision(t_cast_data *d, t_main *g)
{
	t_obj_node	*curr;
	t_door		*door;
	double		min_dist;
	double		dist;

	curr = g->objects.all;
	min_dist = 1000.0;
	while (curr)
	{
		if (curr->type == DOOR)
		{
			door = (t_door *)curr->object;
			if (door->state != OPEN)
			{
				dist = find_collision_distance(d, door->barrier);
				if (dist < min_dist)
					min_dist = dist;
			}
		}
		curr = curr->next;
	}
	return (min_dist);
}

static double	get_min_collision_distance(t_cast_data *d, t_main *g, double max_check)
{
	double	wall_distance;
	double	doorwall_distance;
	double	object_distance;

	wall_distance = check_wall_collision(d, g->map.player.pos, g->map.matrix, max_check);
	doorwall_distance = check_doorwall_collision(d, g->map.matrix);
	object_distance = check_object_collision(d, g);
	if (doorwall_distance < wall_distance)
		wall_distance = doorwall_distance;
	if (object_distance < wall_distance)
		wall_distance = object_distance;
	return (wall_distance);
}

static double	check_single_axis(t_cast_data *d, t_main *g, double movement)
{
	double	abs_movement;
	double	min_dist;
	double	max_move;
	double	sign;

	abs_movement = fabs(movement);
	if (abs_movement < 0.0001)
		return (0);
	min_dist = get_min_collision_distance(d, g, abs_movement + PLAYER_RADIUS + 1.5);
	max_move = min_dist - PLAYER_RADIUS;
	if (max_move <= 0)
		return (0);
	sign = (movement > 0) ? 1.0 : -1.0;
	if (abs_movement <= max_move)
		return (movement);
	return (max_move * sign);
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
