/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:12:55 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/29 12:14:38 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p

#include "main.h"
#include <math.h>
#include <stdio.h>

static double	calculate_object_distance(t_player *player, t_obj_node *obj)
{
	double	dx;
	double	dy;
	t_door	*door;

	if (obj->type == DOOR)
	{
		door = (t_door *)obj->object;
		dx = (door->barrier_1.s.x + door->barrier_1.e.x) / 2.0 - player->pos.x;
		dy = (door->barrier_1.s.y + door->barrier_1.e.y) / 2.0 - player->pos.y;
	}
	else
	{
		dx = 0;
		dy = 0;
	}
	return (dx * dx + dy * dy);
}

static double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

static int	do_angular_ranges_overlap(double start1, double end1,
									double start2, double end2)
{
	if (start1 <= end1 && start2 <= end2)
		return (fmax(start1, start2) <= fmin(end1, end2));
	if (start1 > end1)
		return (do_angular_ranges_overlap(start1, 2 * M_PI, start2, end2)
			|| do_angular_ranges_overlap(0, end1, start2, end2));
	if (start2 > end2)
		return (do_angular_ranges_overlap(start1, end1, start2, 2 * M_PI)
			|| do_angular_ranges_overlap(start1, end1, 0, end2));
	return (0);
}

static int	is_object_in_fov(t_player *player, t_obj_node *obj)
{
	t_door		*door;
	double		angle1, angle2;
	double		fov_rad;
	double		player_angle_start, player_angle_end;
	double		object_angle_start, object_angle_end;

	door = (t_door *)obj->object;
	angle1 = normalize_angle(atan2(door->barrier_1.s.y - player->pos.y,
				door->barrier_1.s.x - player->pos.x));
	angle2 = normalize_angle(atan2(door->barrier_1.e.y - player->pos.y,
				door->barrier_1.e.x - player->pos.x));
	fov_rad = FOV * (M_PI / 180.0);
	player_angle_start = normalize_angle(player->dov - (fov_rad / 2.0));
	player_angle_end = normalize_angle(player->dov + (fov_rad / 2.0));
	object_angle_start = fmin(angle1, angle2);
	object_angle_end = fmax(angle1, angle2);
	if (object_angle_end - object_angle_start > M_PI)
	{
		double temp = object_angle_start;
		object_angle_start = object_angle_end;
		object_angle_end = temp;
	}
	return (do_angular_ranges_overlap(player_angle_start, player_angle_end,
			object_angle_start, object_angle_end));
}

// retrieves a ray from the packed ray list structure by screen column
static t_ray	*get_ray_from_list(t_ray_list *list, int x)
{
	t_ray_node	*curr_node;

	curr_node = list->head;
	while (curr_node)
	{
		if (x < list->package_size)
			return (&curr_node->ray_pack[x]);
		x -= list->package_size;
		curr_node = curr_node->next;
	}
	return (NULL);
}

static t_ray_node	*init_cast_data(t_cast_data *d, t_main *g)
{
	d->fov_rad = FOV * (M_PI) / 180.0;
	d->direction = g->map.player.dov - (d->fov_rad / 2.0);
	d->player = &g->map.player;
	return (g->rays.head);
}
// note to my self
// think about remove the fucking t_cast_data XD you know why
// 
void	render_objects(t_main *g, t_cast_data *d)
{
	t_obj_node	*curr;
	double		dist;
	t_door		*door;

	clear_render_queue(&g->objects);
	curr = g->objects.all;
	while (curr)
	{
		if (curr->type == DOOR)
		{
			if (is_object_in_fov(&g->map.player, curr))
			{
				dist = calculate_object_distance(&g->map.player, curr);
				add_to_render_queue(&g->objects, curr, dist);
			}
		}
		// add fireball
		curr = curr->next;
	}
	curr = g->objects.to_render;
	t_ray		tmp_ray;
	d->ray = &tmp_ray;
	int z = 0;
	while (curr)
	{
		printf("rendering door %d\n", z);
		if (curr->type == DOOR)
		{
			t_door *door = (t_door *)curr->object;
			int	i = -1;
			init_cast_data(d, g);
			while (++i < WIN_WIDTH)
			{
				t_ray	*old_ray = get_ray_from_list(&g->rays, i);
				d->ray_d.x = cos(d->direction);
				d->ray_d.y = sin(d->direction);
				if (!find_intersection(d, door->barrier_1)) // need to add fucking barrier_2
				{
					d->direction += d->fov_rad / WIN_WIDTH;
					continue ;
				}
				if (d->ray->distance > old_ray->distance)
				{
					d->direction += d->fov_rad / WIN_WIDTH;
					continue ;
				}
				d->ray->distance *= cos(d->direction - g->map.player.dov);
				int	height = (int)(WIN_HEIGHT / d->ray->distance);
				int start = (-height / 2) + (WIN_HEIGHT / 2);
				if (start < 0)
					start = 0;
				int end = (height / 2) + (WIN_HEIGHT / 2);
				if (end >= WIN_HEIGHT)
					end = WIN_HEIGHT - 1;
				int y = start - 1;
				while (++y <= end)
				{
					if (z%3==1 && y % 7)
						continue ;
					if (z%3==2 && y % 5)
						continue ;
					if (z % 3 == 1)
						put_pixel(i, y, 0xFF0000, &g->window);
					else if (z % 3 == 2)
						put_pixel(i, y, 0x00FF00, &g->window);
					else
						put_pixel(i, y, 0x0000FF, &g->window);
				}
				d->direction += d->fov_rad / WIN_WIDTH;
			}
		}
		// add fireball here
		curr = curr->next_render;
		z++;
	}
}