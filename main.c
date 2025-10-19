/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 08:28:25 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "minilibx/mlx.h"
#include "gc/gc.h"

__attribute__((destructor))
void cya(void)
{
	printf("=== dumpin gc ===\n");
	dump_gc();
	printf("=== dumped gc ===\n");
	printf("=== dumpin crit gc ===\n");
	dump_crit_gc();
	printf("=== dumped crit gc ===\n");
}

static void	_init(t_main *game)
{
	memset(game, 0, sizeof(t_main));
	game->window.mlx = mlx_init(); // connection to mlx for textures
	safe_mlx(game->window.mlx, op_mlx); // insert connection into the safe
	if (!game->window.mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
	game->map.player.pos.x = -1;
	game->map.player.pos.y = -1;
	list_create(&game->rays, WIN_WIDTH * SENSITIVITY * 0.05);
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
	_init(&game);
	// read, validate, parse .cub file
	cub_map(argv[1], &game); // game  goes here because i need to use mlx connection to convert textures
	cub_create_window(&game); // game goes here for memory management stuff 
	// (if you add gc with destructor it can be change to &(game.win))
	// game loop needed here
	
	// dump_gc();
	cub_render(&game, raycasting); // add the render and its done easy right
	mlx_loop(game.window.mlx);
	map_cleanup(&game);
	return 0;
}
