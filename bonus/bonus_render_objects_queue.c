/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render_objects_queue.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 03:02:09 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/02 06:07:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p

#include "main.h"
#include <math.h>

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

static double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

static int	is_segment_in_fov(t_player *p, t_segment *segment)
{
	t_angle	angle;
	t_angle player;
	t_angle	object;
	double	fov_rad;
	double	swap;

	angle.s = normalize_angle(atan2(segment->s.y - p->pos.y,
				segment->s.x - p->pos.x));
	angle.e = normalize_angle(atan2(segment->e.y - p->pos.y,
				segment->e.x - p->pos.x));
	fov_rad = FOV * (M_PI / 180.0);
	player.s = normalize_angle(p->dov - (fov_rad / 2.0));
	player.e = normalize_angle(p->dov + (fov_rad / 2.0));
	object.s = fmin(angle.s, angle.e);
	object.e = fmax(angle.s, angle.e);
	if (object.e - object.s > M_PI)
	{
		swap = object.s;
		object.s = object.e;
		object.e = swap;
	}
	return (do_angular_ranges_overlap(player.s, player.e, object.s, object.e));
}

void	create_render_queue(t_main *g)
{
	t_obj_node	*curr;

	clear_render_queue(&g->objects);
	curr = g->objects.all;
	while (curr)
	{
		if (curr->type == DOOR)
		{
			if (is_segment_in_fov(&g->map.player, &((t_door *)curr->object)->barrier))
				add_to_render_queue(&g->objects, curr, &g->map.player); // i calculate distance in here check inside
		}
		// else add fireball
		// create fireball segment
		// check is segment in fov
		// calc distance and add render queue
		curr = curr->next;
	}
}
