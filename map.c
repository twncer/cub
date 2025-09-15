/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:33:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/09/08 01:46:06 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdlib.h>
#include <stdio.h>  // Added: for printf function

static int	find_id(char *raw_map)
{
	if (raw_map[0] == 'N' && raw_map[1] == 'O' && is_space(raw_map[2]))
		return (0);
	if (raw_map[0] == 'S' && raw_map[1] == 'O' && is_space(raw_map[2]))
		return (1);
	if (raw_map[0] == 'W' && raw_map[1] == 'E' && is_space(raw_map[2]))
		return (2);
	if (raw_map[0] == 'E' && raw_map[1] == 'A' && is_space(raw_map[2]))
		return (3);
	if (raw_map[0] == 'F' && is_space(raw_map[1]))
		return (4);
	if (raw_map[0] == 'C' && is_space(raw_map[1]))
		return (5);
	return (6);
}

static void	check_parsed_table(int parsed[6])
{
	int	i;

	i = -1;
	while (i++ < 6)
	{
		if (parsed[i] == 0)
		{
			printf("Error: Missing map material data\n");
			exit(1);
		}
	}
}

static void	map_parse(char *raw_map, t_main *g)
{
	int			parsed[6] = {0, 0, 0, 0, 0, 0}; // NO SO WE EA F C - when refactoring i found out i dont need map xd
	int			current_id;
	char		*map_start;

	map_start = raw_map;
	while (*raw_map)
	{
		while (*raw_map && (is_space(*raw_map) || *raw_map == '\n'))
		{
			if (*raw_map == '\n')
				map_start = raw_map + 1;
			raw_map++;
		}
		if (*raw_map == '\0')
			break;
		current_id = find_id(raw_map);
		if (current_id < F)
		{
			parse_texture(raw_map, current_id, parsed, g);
			// Advance to next line after processing texture
			while (*raw_map && *raw_map != '\n')
				raw_map++;
		}
		else if (current_id < MAP)
		{
			parse_color(raw_map, current_id, parsed, g);
			// Advance to next line after processing color
			while (*raw_map && *raw_map != '\n')
				raw_map++;
		}
		else
			break ;
	}
	check_parsed_table(parsed);
	parse_matrix(map_start, g);
}

void	cub_map(char *map_file, t_main *game)
{
	char	*raw_map;

	raw_map = cub_map_read(map_file);
	if (!raw_map)
		exit(1);
	map_parse(raw_map, game);
	// check textures one by one
	//test color
	printf("color_f::%d\ncolor_c::%d\n", game->map.color_f, game->map.color_c);
	// matrix
	printf("matrix::\n");
	int i = -1;
	while (game->map.matrix[++i])
	{
		int j = -1;
		while (game->map.matrix[i][++j])
		{
			printf("%d", game->map.matrix[i][j]);	
		}
		printf("\n");
	}
	//player
	printf("player_x::%f\nplayer_y::%f\n", game->map.player.x, game->map.player.y);
	free(raw_map);
}
