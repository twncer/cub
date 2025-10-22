/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/22 20:21:07 by btuncer          ###   ########.fr       */
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
#include "../events/events.h"

static void _init_keys(t_main *game)
{
	game->key_list.w = false;
	game->key_list.a = false;
	game->key_list.s = false;
	game->key_list.d = false;
	game->key_list.arrow_l = false;
	game->key_list.arrow_r = false;
	
	// switch keys
	game->key_list.e.key = false;
	game->key_list.e.key_switch = false;
}

void	__init__(t_main *game)
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

void _init_hooks(t_main *game)
{
	mlx_hook(game->window.win, 2, 1L << 0, onpress_event, game);
	mlx_hook(game->window.win, 3, 1L << 1, onrelease_event, game);
	mlx_hook(game->window.win, 17, 0, terminate_hook, NULL);
	mlx_loop_hook(game->window.mlx, loop_event, game);
}
