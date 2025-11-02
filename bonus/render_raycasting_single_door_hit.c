/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycasting_single_door_hit.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:46:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/02 06:54:33 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

#include <stdio.h>

t_door_wall	*find_door_wall(int x, int y, t_door_wall *new);

static int	check_doorwall_inner_hit(t_cast_data *d, t_door_wall *dw)
{
	if (find_intersection(d, dw->inner_wall_1))
	{
		if (dw->axis == 1)
			d->ray->side = 'W';
		else
			d->ray->side = 'N';
		return (1);
	}
	if (find_intersection(d, dw->inner_wall_2))
	{
		if (dw->axis == 1) 
			d->ray->side = 'E';
		else
			d->ray->side = 'S';
		return (1);
	}
	return 0;
}

static int	insert_doorwall_inner_hit(t_cast_data *d, t_door_wall *dw)
{
    double  wall_hit_pos;
	double	door_start;
	
	door_start = (1.0 - DOOR_WIDTH) / 2.0;
	if (dw->axis == 0)
		wall_hit_pos = d->ray->hit.y - floor(d->ray->hit.y);
	else
		wall_hit_pos = d->ray->hit.x - floor(d->ray->hit.x);
	if (wall_hit_pos > door_start && wall_hit_pos < door_start + DOOR_WIDTH)
	{
		if (check_doorwall_inner_hit(d, dw))
			return (1);
		return (0);
	}
	return (1);
}

int	insert_doorwall_hit(t_cast_data *d, int loc)
{
    t_door_wall	*dw;
	int			side;

	dw = NULL;
	if (loc)
	{
		dw = find_door_wall((int)d->player->pos.x, (int)d->player->pos.y, NULL);
		if (check_doorwall_inner_hit(d, dw))
			return (1);
	}
	else
	{
		dw = find_door_wall(d->map_pos.x, d->map_pos.y, NULL);
		side = d->ray->side;
		if (side == 0)
			insert_horizontal_hit(d);
		else
			insert_vertical_hit(d);
		if (side == dw->axis)
			return (insert_doorwall_inner_hit(d, dw));
		return (1);
	}
	return (0);
}
