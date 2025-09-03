/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:02:54 by yusudemi          #+#    #+#             */
/*   Updated: 2025/09/03 05:34:11 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minilibx/mlx.h"  // Added: for MLX functions
#include <stdlib.h>

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
	if (game->window.mlx)
	{
		mlx_destroy_display(game->window.mlx);
		free(game->window.mlx);
		game->window.mlx = NULL;
	}
	//clear the map struct
	int	i;
	if (game->map.matrix)
	{
		i = -1;
		while (game->map.matrix[++i])
		{
			free(game->map.matrix[i]);
			game->map.matrix[i] = NULL;
		}
		free(game->map.matrix);
		game->map.matrix = NULL;
	}
	// Note: Removed exit(1) - let caller decide whether to exit
}

// Cleanup and exit for error cases
void	map_cleanup_exit(t_main *game)
{
	map_cleanup(game);
	exit(1);
}