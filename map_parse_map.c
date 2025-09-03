/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:07:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/09/03 05:34:20 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>   // Added: for printf function
#include "utils.h"  // Added: for is_space function

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_space(c)
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int get_map_height(char *raw_map)
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
		{
			printf("Error: Map has invalid character\n");
			exit(1);
		}
		else
			ret = count;
		raw_map++;
	}
	return (ret);
}

static int	char_to_int(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else if (c == '1')
		return (2);
	else if (is_space(c)) // placeholders in map line to correctly visialize map
		return (3);
	return (83);
}

// put 2 for spaces as placeholder. continue on rawmap including nl ((*rawmap)++) 
int	*create_map_line(char **raw_map)
{
	int	*map_line;
	int	line_len;
	int	*ret;

	line_len = 0;
	while ((*raw_map)[line_len] && (*raw_map)[line_len] != '\n')
		line_len++;
	map_line = malloc(sizeof(int) * (line_len + 1));
	if (!map_line)
	{
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	ret = map_line;
	while (**raw_map && **raw_map != '\n')
	{
		(*map_line) = char_to_int(**raw_map);
		map_line++;
		(*raw_map)++;
	}
	(*map_line) = 0;
	return (ret);
}

int	**create_matrix(char *raw_map)
{
	int	**map;
	int	map_height;
	int	i;

	if (!*raw_map)
	{
		printf("Error: Missing map data\n");
		exit(1);
	}
	map_height = get_map_height(raw_map);
	map = malloc (sizeof(int *) * (map_height + 1));
	if (!map)
	{
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	map[map_height] = NULL;
	i = -1;
	while (i++ < map_height)
	{
		if (*raw_map == '\n')
			continue;
		map[i] = create_map_line(&raw_map);
		if (!map[i]) // needed
		{
			while (--i >= 0)
				free(map[i]);
			free(map);  // Added: free the map array itself
			printf("Error: Memory allocation failed\n");
			exit(1);
		}
	}
	return (map);
}
