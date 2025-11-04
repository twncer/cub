/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/04 16:16:59 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <math.h>
#include <stdio.h>

static void render_main_menu(t_main *g)
{
	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 0);
	place_button(g, &g->main_menu.btn_start);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

static void render_game(t_main *g)
{
	render_background(g);
	render_scene(g);
	render_objects(g);
	// do raycasting and store its data
	// according to raycasting data
	// render walls and image that you make
	// put all this shit on screen yay

	draw_minimap(g);
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}

void	cub_render(t_main *g)
{	
	if (g->main_menu.active)
		render_main_menu(g);
	else
		render_game(g);
}
