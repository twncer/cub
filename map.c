/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:33:47 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 08:38:24 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "main.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	validate_extension(char	*map_loc);
static char	*process_materials(char *raw_map);

void	cub_map(char *map_location)
{
	int		fd;
	char	*raw_map;
	// validate ext
	if (!validate_extension(map_location))
	{
		cleanup("map file extension must be `.cub`!");
	}
	// read map
	fd = open(map_location, O_RDONLY, 0666);
	if (fd == -1)
	{
		printf("Error: Cannot open map file\n");
		exit(1); // also add here
	}
	raw_map = cub_map_read(fd);
	close(fd);
	// validate and parse (now with texture loading using MLX)
	cub_map_process(raw_map);
	free(raw_map);
}

static int	validate_extension(char	*map_loc)
{
	int	len;

	len = strlen(map_loc);
	if (len < 4 || strcmp(map_loc + len - 4, ".cub") != 0)
		return (0);
	return (1);
}
