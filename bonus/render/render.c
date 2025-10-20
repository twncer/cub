/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/20 21:27:47 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <math.h>
#include <stdio.h>

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