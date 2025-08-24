/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 07:52:38 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 08:38:14 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static int	check_file_extension(char *path)
{
	int path_len;

	while (path[path_len])
		path_len++;
	if (path_len < 4
		|| ft_strcmp(path + path_len - 4, ".xpm") != 0
		|| ft_strcmp(path + path_len - 4, ".png") != 0)
	{
		free(path);
		cleanup("Texture file must have .xpm or .png extension");
	}
	else if (ft_strcmp(path + path_len - 4, ".xpm") == 0)
		return (0);
	return (1);
}

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
		cleanup("Missing texture file");
	path = malloc(path_len + 1);
	if (!path)
		cleanup("Memory allocation failed");
	i = -1;
	while (i++ < path_len)
		path[i] = path_start[i];
	path[i] = '\0';
	return (path);
}

static int	check_file_extension(char *path)
{
	int		path_len;
	int		fd;

	path_len = strlen(path);
	if (path_len < 4)
		cleanup("Invalid texture file path");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		cleanup("Cannot open texture file");
	close(fd);
	if (strcmp(path + path_len - 4, ".xmp") == 0)
		return (0);
	else if (strcmp(path + path_len - 4, ".png") == 0)
		return (1);
	else
		cleanup("Texture file must have .xmp or .png extension");
	return (83);
}

void	validate_texture(char *raw_map, int id, int parsed[6])
{
	char	*path;
	int		line_len;
	int		fd;
	int 	ext;

	if (parsed[id])
		cleanup("Duplicate texture identifier");
	path = extract_texture_path(raw_map);
	ext = check_file_extension(path);
	map_parse_texture(id, path, ext);
	parsed[id] = 1;
}
