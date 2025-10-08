/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 05:18:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#include <stdio.h>

void	render_scene(t_main *g)
{
	(void)g;
	// idk how to put walls
	// fuck fuck fuck fuck
	// brainded
}

void	cub_render(t_main *g, t_raycasting_func raycast)
{
	// check if player is in map
	// if not render black screen xd
	//get background colors and put it on addr ptr // render_background
	render_background(g);
	printf("Floor color (F): %d (0x%06X)\n", g->map.color_f, g->map.color_f);
	printf("Ceiling color (C): %d (0x%06X)\n", g->map.color_c, g->map.color_c);
	// do raycasting and store its data
	raycast(g);
	// according to raycasting data
	// render walls and image that you make
	render_scene(g);
	// put all this shit on screen yay
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}