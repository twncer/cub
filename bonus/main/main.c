/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/20 22:05:29 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "../minilibx/mlx.h"
#include "../gc/gc.h"
#include "../player/player.h"
#include <X11/keysym.h>

__attribute__((destructor))
void cya(void)
{
	dump_crit_gc();
}

int onpress_event(int key, t_main *game)
{
	if (key == KEY_W)
		game->key_list.W = true;
	else if (key == KEY_A)
		game->key_list.A = true;
	else if (key == KEY_S)
		game->key_list.S = true;
	else if (key == KEY_D)
		game->key_list.D = true;
	return (0);
}

int onrelease_event(int key, t_main *game)
{
	if (key == XK_Escape)
		exit(0);

	if (key == KEY_W)
		game->key_list.W = false;
	else if (key == KEY_A)
		game->key_list.A = false;
	else if (key == KEY_S)
		game->key_list.S = false;
	else if (key == KEY_D)
		game->key_list.D = false;
	return (0);
}

int terminate_hook(void)
{
	printf("dont kill me :c\n");
	exit(0);
	return (0);
}

static void _init_keys(t_main *game)
{
	game->key_list.W = false;
	game->key_list.A = false;
	game->key_list.S = false;
	game->key_list.D = false;
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
	_init_keys(game);
	list_create(&game->rays, WIN_WIDTH * SENSITIVITY * 0.05);
}

int loop_event(t_main *game)
{
	char w, a, s, d;
	if (game->key_list.W) w = 'W';
	else w = ' ';
	if (game->key_list.A) a = 'A';
	else a = ' ';
	if (game->key_list.S) s = 'S';
	else s = ' ';
	if (game->key_list.D) d = 'D';
	else d = ' ';
	printf("\n\n\n        (%c)     \n(%c)     (%c)     (%c)\n", w, a, s, d);

	change_position(game, 0);
	usleep(500);
	return (0);
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
	
	dump_gc();
	cub_render(&game, raycasting); // add the render and its done easy right
	
	mlx_hook(game.window.win, 2, 1L << 0, onpress_event, &game);
	mlx_hook(game.window.win, 3, 1L << 1, onrelease_event, &game);
	mlx_hook(game.window.win, 17, 0, terminate_hook, NULL);
	
	mlx_loop_hook(game.window.mlx, loop_event, &game);
	mlx_loop(game.window.mlx);

	map_cleanup(&game);
	return 0;
}
