/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_single.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:50:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/02 06:54:33 by yusudemi         ###   ########.fr       */
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

void	insert_horizontal_hit(t_cast_data *d)
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

void	insert_vertical_hit(t_cast_data *d)
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
		d->ray->hit.y = d->map_pos.y + 1.0;
	}
	d->ray->hit.x = d->player->pos.x +
		(d->ray->distance * d->ray_d.x);
}

static void	raycast_loop(t_cast_data *d, char **matrix)
{
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
		if (matrix[d->map_pos.y][d->map_pos.x] == 'D')
			if (insert_doorwall_hit(d, 0))
				return ;
		if (matrix[d->map_pos.y][d->map_pos.x] == '1')
			break ;
	}
}

void	raycast_single(t_cast_data *d, char **matrix)
{
	d->map_pos.x = (int)d->player->pos.x;
	d->map_pos.y = (int)d->player->pos.y;
	find_ray_direction(d);
	raycast_loop(d, matrix);
	// adding door if in door block
	if (matrix[(int)d->player->pos.y][(int)d->player->pos.x] == 'D')
		if (insert_doorwall_hit(d, 1))
			return ;
	if (d->ray->side > 2)
		return ;
	if (d->ray->side == 0)
		insert_horizontal_hit(d);
	else
		insert_vertical_hit(d);
}
