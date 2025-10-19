/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:02:54 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 09:35:44 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>

void	map_cleanup(t_main *game)
{
	//before destroy the connection need to clear textures
	if (game->window.mlx)
	{
		if (game->map.texture_no.img)
			mlx_destroy_image(game->window.mlx, game->map.texture_no.img);
		if (game->map.texture_so.img)
			mlx_destroy_image(game->window.mlx, game->map.texture_so.img);
		if (game->map.texture_we.img)
			mlx_destroy_image(game->window.mlx, game->map.texture_we.img);
		if (game->map.texture_ea.img)
			mlx_destroy_image(game->window.mlx, game->map.texture_ea.img);
	}
	//close mlx connection which opened at _init at main
	// if (game->window.mlx)
	// {
	// 	mlx_destroy_display(game->window.mlx);
	// 	free(game->window.mlx);
	// 	game->window.mlx = NULL;
	// }
	//clear the map struct
	
	//int	i;
	// if (game->map.matrix) HERE1
	// {
	// 	i = -1;
	// 	while (game->map.matrix[++i])
	// 	{
	// 		free(game->map.matrix[i]);
	// 		game->map.matrix[i] = NULL;
	// 	}
	// 	free(game->map.matrix);
	// 	game->map.matrix = NULL;
	// } HERE1
}

// cleanup and exit for error cases
void	map_cleanup_exit(char *errmsg, t_main *game)
{
	printf("%s\n", errmsg);
	map_cleanup(game);
	exit(1);
}