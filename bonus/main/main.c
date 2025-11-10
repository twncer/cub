/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/10 15:04:01 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "../minilibx/mlx.h"
#include "../minilibx/mlx_int.h"
#include "../gc/gc.h"
#include "../player/player.h"
#include "../events/events.h"

#include <X11/keysym.h>

__attribute__((destructor))
void cya(void)
{
	dump_crit_gc();
}

int main(int argc, char **argv)
{
	t_main game; // this is the struct that keeps all data
	
	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return 1;
	}
	// initialize game struct and create mlx connection to use mlx_xpm_file_to_image in cub_map
	__init__(&game);
	// read, validate, parse .cub file
	cub_map(argv[1], &game); // game  goes here because i need to use mlx connection to convert textures
	cub_objects(&game); // creates objects
	
	cub_create_window(&game); // game goes here for memory management stuff 
	// (if you add gc with destructor it can be change to &(game.win))
	
	// game loop needed here
	dump_gc();

	// mlx_mouse_hide(game.window.mlx, game.window.win);
	// cub_render(&game); // add the render and its done easy right
	_init_hooks(&game);

	center_window(&game);
	
	mlx_loop(game.window.mlx);
	map_cleanup(&game);
	return 0;
}
