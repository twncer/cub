/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 07:52:38 by yusudemi          #+#    #+#             */
/*   Updated: 2025/09/03 05:49:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static char	*extract_texture_path(char *path_start)
{
	char	*path_end;
	char	*path;
	int		path_len;
	int		i;

	path_start += 2;
	while (*path_start && is_space(*path_start))
		path_start++;
	path_end = path_start;
	while (*path_end && !is_space(*path_end) && *path_end != '\n')
		path_end++;
	path_len = path_end - path_start;
	if (path_len == 0)
	{
		printf("Error: Missing texture file\n");
		exit(1);
	}
	path = malloc(path_len + 1);
	if (!path)
	{
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	i = -1;
	while (i++ < path_len)
		path[i] = path_start[i];
	path[i] = '\0';
	return (path);
}

static void	check_file_extension(char *path)
{
	int		path_len;
	int		fd;

	path_len = strlen(path);
	if (path_len < 4)
	{
		printf("Error: Invalid texture file path\n");
		exit(1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open texture file\n");
		exit(1);
	}
	if (strcmp(path + path_len - 4, ".xpm") != 0)
	{
		printf("Error: Texture file must have .xpm extension\n");
		exit(1);
	}
}

static t_texture	*find_target_texture(int id, t_map *map)
{
	if (id == NO)
		return (&map->texture_no);
	else if (id == SO)
		return (&map->texture_so);
	else if (id == WE)
		return (&map->texture_we);
	else if (id == EA)
		return (&map->texture_ea);
	return (NULL);
}

static void set_texture(int id, char *path, t_main *g)
{
	t_texture *target_texture;

	target_texture = find_target_texture(id, &(g->map));
	target_texture->img = mlx_xpm_file_to_image(g->window.mlx, path, 
		&target_texture->width, &target_texture->height);
	free(path);
	if (!target_texture->img)
	{
		printf("Error: Failed to load texture image\n");
		exit(1);
	}
	target_texture->addr = mlx_get_data_addr(target_texture->img,
		&target_texture->bits_per_pixel, &target_texture->line_length,
		&target_texture->endian);
	if (!target_texture->addr)
	{
		printf("Error: Failed to get texture data address\n");
		exit(1);
	}
}

void	parse_texture(char *raw_map, int id, int parsed[6], t_main *g)
{
	char	*path;

	if (parsed[id])
	{
		printf("Error: Duplicate texture identifier\n");
		exit(1);
	}
	path = extract_texture_path(raw_map);
	check_file_extension(path);
	set_texture(id, path, g);
	parsed[id] = 1;
}
