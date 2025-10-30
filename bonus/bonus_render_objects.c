/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:12:55 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/30 09:15:27 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p

#include "main.h"
#include <math.h>
#include <stdio.h>

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

static int	get_pixel_color(t_window *win, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return (0);
	dst = win->addr + (y * win->line_length + x * (win->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static int	blend_colors(int bg_color, int fg_color, double alpha)
{
	int	bg_r;
	int	bg_g;
	int	bg_b;
	int	fg_r;
	int	fg_g;
	int	fg_b;
	int	r;
	int	g;
	int	b;

	bg_r = (bg_color >> 16) & 0xFF;
	bg_g = (bg_color >> 8) & 0xFF;
	bg_b = bg_color & 0xFF;
	fg_r = (fg_color >> 16) & 0xFF;
	fg_g = (fg_color >> 8) & 0xFF;
	fg_b = fg_color & 0xFF;
	r = (int)(fg_r * alpha + bg_r * (1.0 - alpha));
	g = (int)(fg_g * alpha + bg_g * (1.0 - alpha));
	b = (int)(fg_b * alpha + bg_b * (1.0 - alpha));
	return ((r << 16) | (g << 8) | b);
}

// note to my self
// think about remove the fucking t_cast_data XD you know why
// 
static void draw_door_column(t_main *g, int x, t_ray *ray)
{
	int		height;
	int		start;
	int		end;
	int		y;
	int		field_color;
	int		bg_color;
	int		final_color;
	double	alpha;

	height = (int)(WIN_HEIGHT / ray->distance);
	start = (-height / 2) + (WIN_HEIGHT / 2);
	if (start < 0)
		start = 0;
	end = (height / 2) + (WIN_HEIGHT / 2);
	if (end >= WIN_HEIGHT)
		end = WIN_HEIGHT - 1;
	y = start - 1;
	field_color = 0xFF4990;
	alpha = 0.4;
	while (++y <= end)
	{
		bg_color = get_pixel_color(&g->window, x, y);
		final_color = blend_colors(bg_color, field_color, alpha);
		put_pixel(x, y, final_color, &g->window);
	}
}

static void	init_cast_data(t_cast_data *d, t_main *g, t_ray *ray)
{
	d->fov_rad = FOV * (M_PI) / 180.0;
	d->direction = g->map.player.dov - (d->fov_rad / 2.0);
	d->player = &g->map.player;
	d->ray = ray;
}
// todo: fucking delete the barrier 2 if you really want it add it as a seperate obj 
// but my suggestion dont fucking lost time on it xd
static void	render_door(t_main *g, t_door *door)
{
	t_cast_data	d;
	t_ray		ray;
	int			x;
	
	init_cast_data(&d, g, &ray);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		t_ray	*old_ray = get_ray_from_list(&g->rays, x);
		d.ray_d.x = cos(d.direction);
		d.ray_d.y = sin(d.direction);
		if (!find_intersection(&d, door->barrier_1))
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		if (d.ray->distance > old_ray->distance)
		{
			d.direction += d.fov_rad / WIN_WIDTH;
			continue ;
		}
		d.ray->distance *= cos(d.direction - g->map.player.dov);
		draw_door_column(g, x, &ray);
		d.direction += d.fov_rad / WIN_WIDTH;
	}
}

void	render_objects(t_main *g, t_cast_data *d)
{
	t_obj_node	*curr;
	t_door		*door;

	clear_render_queue(&g->objects);
	create_render_queue(g);
	curr = g->objects.to_render;
	t_ray		tmp_ray;
	int z = 0;
	while (curr)
	{
		if (curr->type == DOOR)
			render_door(g, curr->object);
		// add fireball here xd
		curr = curr->next_render;
		z++;
	}
}
