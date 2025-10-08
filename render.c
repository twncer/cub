/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 06:28:52 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdio.h>

static int	get_wall_color(char wall_side)
{
	if (wall_side == 'N')
		return (0xFF0000); // red
	else if (wall_side == 'S')
		return (0x00FF00); // green
	else if (wall_side == 'E')
		return (0x0000FF); // blue
	else if (wall_side == 'W')
		return (0xFFFF00); // yellow
	return (0xFFFFFF); // white if something fuckedup
}

static void	draw_wall_column(t_main *g, int x, t_ray *ray)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
	int	y;
	
	line_height = (int)(WIN_HEIGHT / ray->distance);
	draw_start = (-line_height / 2) + (WIN_HEIGHT / 2);
	if (draw_start < 0) // only render for window
		draw_start = 0;
	draw_end = (line_height / 2) + (WIN_HEIGHT / 2);
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	// color for debug change this to textures later
	color = get_wall_color(ray->side);
	y = draw_start - 1;
	while (++y <= draw_end)
		put_pixel(x, y, color, &g->window);
}

void	render_scene(t_main *g)
{
	t_ray_node	*current;
	int			x;
	
	current = g->rays.head;
	x = -1;
	while (current && ++x < WIN_WIDTH)
	{
		draw_wall_column(g, x, &current->ray);
		current = current->next;
	}
}

void	cub_render(t_main *g, t_raycasting_func raycast)
{
	// check if player is in map
	// if not render black screen xd
	//get background colors and put it on addr ptr // render_background
	render_background(g);
	// do raycasting and store its data
	raycast(g);
	// according to raycasting data
	// render walls and image that you make
	render_scene(g);
	// put all this shit on screen yay
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}