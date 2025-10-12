/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/12 09:23:32 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>
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

void	render_black_screen(t_window *win)
{
	int black;
	int	y;
	int x;

	printf("rendering the fucking black screen >&\n");
	black = 0x000000;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			put_pixel(x,y,black,win);
		}
	}
}

int check_off_map(t_main *g)
{
	double	width;
	double	height;

	if (g->map.player.pos.y < 0.0 || g->map.player.pos.x < 0.0)
		return (1);
	height = 0.0;
	while (g->map.matrix[(int)height])
		height += 1.0;
	if (g->map.player.pos.y >= height)
		return (1);
	width = 0.0;
	while (g->map.matrix[(int)g->map.player.pos.y][(int)width])
		width += 1.0;
	if (g->map.player.pos.x >= width)
		return (1);
	return (0);
}

void	cub_render(t_main *g, t_raycasting_func raycast)
{
	// check if player is in map
	// if not render black screen xd
	//get background colors and put it on addr ptr // render_background
	if (raycast == raycasting && check_off_map(g))
		render_black_screen(&g->window);
	else
	{
		render_background(g);
		raycast(g);
		render_scene(g);
	}
	// do raycasting and store its data
	// according to raycasting data
	// render walls and image that you make
	// put all this shit on screen yay
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}