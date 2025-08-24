/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:43:48 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 08:52:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

static int	find_id(char *raw_map);
static void	check_parsed_table(int parsed[6]);
	// obj->for first six non empty line and validate and parse it.
	// skip any kind of tab and space nl etc in raw_map
	// check if line is valid find its type
	// parse the line according to its type and !mark it on parsed table!
void	cub_map_process(char *raw_map)
{
	int			parsed[6] = {0, 0, 0, 0, 0, 0}; // NO SO WE EA F C - when refactoring i found out i dont need map xd
	int			current_id;
	char		*map_start;

	map_start = raw_map;
	while (*raw_map)
	{
		while (*raw_map && (is_space(*raw_map) || *raw_map == '\n'))
		{
			if (raw_map == '\n')
				map_start = raw_map + 1;
			raw_map++;
		}
		if (*raw_map == '\0')
			break;
		current_id = find_id(raw_map);
		if (current_id < F)
			validate_texture(raw_map, current_id, parsed);
		else if (current_id < MAP)
			validate_color(raw_map, current_id, parsed);
		else
			break ;
	}
	check_parsed_table(parsed);
	validate_map(map_start);
}

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
			cleanup("Missing map material data");
	}
}