/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_raycast_single_intersection.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 23:07:05 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/25 23:22:10 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

int check_intersection(t_cast_data *d, t_segment inner_wall)
{

	
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

int find_intersection(t_cast_data *d, t_segment inner_wall)
{
	t_vector	wall_d;
	t_vector	ray_d;
	double		det;
	double		dt_wall;
	double		dt_ray;
	
	wall_d.x = inner_wall.e.x - inner_wall.s.x;
	wall_d.y = inner_wall.e.y - inner_wall.s.y;
	det = d->ray_d.x * wall_d.y - d->ray_d.y * wall_d.x;
	if (fabs(det) < 1e-10)
		return (0);
	ray_d.x = inner_wall.s.x - d->player->pos.x;
	ray_d.y = inner_wall.s.y - d->player->pos.y;
	dt_ray = (ray_d.x * wall_d.y - ray_d.y * wall_d.x) / det;
	dt_wall = (ray_d.x * d->ray_d.y - ray_d.y * d->ray_d.x) / det;
	if (dt_ray > 0 && dt_wall >= 0.0 && dt_wall <= 1.0)
	{
		d->ray->hit.x = d->player->pos.x + dt_ray * d->ray_d.x;
		d->ray->hit.y = d->player->pos.y + dt_ray * d->ray_d.y;
		d->ray->distance = dt_ray;
		return (1);
	}
	return (0);
}
