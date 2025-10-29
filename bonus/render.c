/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/29 06:54:53 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>
#include <stdio.h>

void	cub_render(t_main *g, t_raycasting_func raycast)
{
	t_cast_data		cast_data;
	// check if player is in map
	// if not render black screen xd
	//get background colors and put it on addr ptr // render_background
	if (raycast == raycasting && check_off_map(g))
		render_black_screen(&g->window);
	else
	{
		render_background(g);
		raycast(g, &cast_data);
		render_scene(g);
		render_objects(g, &cast_data);
	}
	// put all this shit on screen yay
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}