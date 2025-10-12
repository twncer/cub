/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:25:35 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/12 11:43:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>

static t_texture	*get_wall_texture(t_main *g, char wall_side)
{
	if (wall_side == 'N')
		return (&g->map.texture_no);
	else if (wall_side == 'S')
		return (&g->map.texture_so);
	else if (wall_side == 'E')
		return (&g->map.texture_ea);
	else if (wall_side == 'W')
		return (&g->map.texture_we);
	return (&g->map.texture_no);
}

static void	init_render_data(t_render_data *d, t_main *g, t_ray *ray)
{
	d->wall_texture = get_wall_texture(g, ray->side);
	d->wall_height = (int)(WIN_HEIGHT / ray->distance);
	d->wall_start = (-d->wall_height / 2) + (WIN_HEIGHT / 2);
	if (d->wall_start < 0)
		d->wall_start = 0;
	d->wall_end = (d->wall_height / 2) + (WIN_HEIGHT / 2);
	if (d->wall_end < 0)
		d->wall_end = 0;
	if (ray->side == 'N' || ray->side == 'S')
		d->wall_hit = ray->hit.x;
	else // ray->side == 'E' || ray->side == 'W'
		d->wall_hit = ray->hit.y;
	d->wall_hit = d->wall_hit - floor(d->wall_hit);
}

static void	draw_wall_column(t_main *g, int x, t_ray *ray)
{
	t_render_data	d;
	int				y;
	int				color;
	
	init_render_data(&d, g, ray);
	d.texture_x = (int)(d.wall_hit * (double)d.wall_texture->width);
	d.texture_x = d.wall_texture->width - d.texture_x - 1;
	d.texture_step = (double)d.wall_texture->height / d.wall_height;
	d.texture_pos = (d.wall_start - WIN_HEIGHT / 2 + d.wall_height / 2) * d.texture_step;
	y =	d.wall_start - 1;
	while (++y <= d.wall_end)
	{
		d.texture_y = (int)d.texture_pos & (d.wall_texture->height - 1);
		d.texture_pos += d.texture_step;
		color = *(int *)(d.wall_texture->addr + (d.texture_y * d.wall_texture->line_length + d.texture_x * (d.wall_texture->bits_per_pixel / 8)));
		put_pixel(x, y, color, &g->window);
	}
}

void	render_scene(t_main *g)
{
	t_ray_node	*current;
	int			i;
	int			j;
	
	current = g->rays.head;
	i = -1;
	while (current && ++i < g->rays.list_size)
	{
		j = -1;
		while (++j < g->rays.package_size)
			draw_wall_column(g, j + (i * g->rays.package_size), &(current->ray_pack[j]));
		current = current->next;
	}
}
