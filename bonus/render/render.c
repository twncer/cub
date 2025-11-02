/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/31 07:11:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include "../hud/minimap/minimap.h"
#include <math.h>
#include <stdio.h>

void	cub_render(t_main *g)
{
	render_background(g);
	render_scene(g);
	// do raycasting and store its data
	// according to raycasting data
	// render walls and image that you make
	// put all this shit on screen yay

	draw_minimap(g);
	draw_image(&g->window, &g->img, 500, 400);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}
