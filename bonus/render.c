/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:41:45 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/28 01:43:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <math.h>
#include <stdio.h>

void	iter_objects()
{
	t_door_wall	*door;
	int			i;

	i = -1;
	while (++i)
	{
		door = find_door(-1, i, NULL);
		if (!door)
			break ;
		
	}


}

void	render_objects(t_main *g)
{
	// itirate all objects fireball and doors
	// if its in player->dov && if its distance < current g.ray.distance if its get them
	// sort them and render
	// sort them by distance and check 
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
		// render_objects(g);
	}
	// put all this shit on screen yay
	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
}