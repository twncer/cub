/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:07:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/01 18:28:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_space(c)
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int get_map_height(char *raw_map, t_main *g)
{
	int	count;
	int	ret;

	count = 1;
	ret = 0;
	while (*raw_map)
	{
		if (*raw_map == '\n')
			count++;
		else if (!is_valid_map_char(*raw_map))
			map_cleanup_exit("Error: Map has invalid character", g);
		else
			ret = count;
		raw_map++;
	}
	return (ret);
}

static int	char_to_int(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (48);
	else if (c == '1')
		return (49);
	else if (is_space(c)) // placeholders in map line to correctly visialize map
		return (50);
	return (83);
}

void	parse_player_view(t_main *g, char direction)
{
	if (direction == 'W')
		g->map.player.view_ref_x = -1;
	if (direction == 'E')
		g->map.player.view_ref_x = 1;
	if (direction == 'N')
		g->map.player.view_ref_y = -1;
	if (direction == 'S')
		g->map.player.view_ref_y = 1;
}

// put 2 for spaces as placeholder. continue on rawmap including nl ((*rawmap)++) 
static char	*create_map_line(char **raw_map, t_main *g)
{
	char	*matrix_line;
	int	i;
	int	line_len;

	line_len = 0;
	while ((*raw_map)[line_len] && (*raw_map)[line_len] != '\n')
		line_len++;
	matrix_line = malloc(sizeof(char) * (line_len + 1));
	if (!matrix_line)
		return (NULL);
	i = -1;
	while (++i < line_len)
	{
		matrix_line[i] = char_to_int(**raw_map);
		if (**raw_map == 'N' || **raw_map == 'S'
			|| **raw_map == 'E' || **raw_map == 'W')
		{
			if (g->map.player.x != -1)
				map_cleanup_exit("Error: map must include only one player", g);
			parse_player_view(g, **raw_map);
			g->map.player.x = i + 0.5;
			g->map.player.view_ref_x += g->map.player.x;
		}
		(*raw_map)++;
	}
	(*raw_map)++;
	matrix_line[i] = 0;
	return (matrix_line);
}

int	create_matrix(char *raw_map, t_main *g)
{
	int	matrix_height;
	int	player;
	int	i;

	matrix_height = get_map_height(raw_map, g);
	g->map.matrix = malloc(sizeof(char *) * (matrix_height + 1));
	if (!g->map.matrix)
		map_cleanup_exit("Error: Memory allocation failed", g);
	g->map.matrix[matrix_height] = NULL;
	i = -1;
	player = 0;
	while (++i < matrix_height)
	{
		g->map.matrix[i] = create_map_line(&raw_map, g);
		if (g->map.player.x != -1 && !player)
		{
			player = 1;
			g->map.player.y += i + 0.5;
			printf("{[[%f]]}\n", g->map.player.view_ref_y);
			g->map.player.view_ref_y += g->map.player.y;
		}
		if (!g->map.matrix[i])
			map_cleanup_exit("Error: Memory allocation failed", g);
	}
	if (g->map.player.x == -1)
		map_cleanup_exit("Error: map must include a player", g);
	return (matrix_height);
}
