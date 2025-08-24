/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:23:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/21 11:59:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "minilibx/mlx.h"

static void	_init(t_main *game);
static t_main	*pointer_storage(t_main	*game);

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
	// read, validate, parse map
	cub_map(argv[1]);

	cleanup(NULL);
	return 0;
}

static void	_init(t_main *game)
{
	memset(game, 0, sizeof(t_main));
	pointer_storage(game);
	game->window.mlx = mlx_init();
	if (!game->window.mlx)
	{
		printf("Error: Failed to initialize MLX\n");
		exit(1);
	}
}

void	cleanup(const char *msg)
{
	t_main *game;

	game = pointer_storage(NULL);
	// need a cleanup to use in all functions for now i leave it blank
	// code it when you complete all structs
	if (msg)
	{
		printf("Error: %s\n", msg);
		exit(1);
	}
}

t_main	*pointer_storage(t_main	*game)
{
	static t_main	*stored;

	if (game)
	{
		stored = game;
		return (NULL);
	}
	return (stored);
}