/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:41:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/21 08:54:05 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "main.h"

static void	read_error(char *msg, char *raw_map, int fd);

// for efficiency i read all map data at once. dont touch! line by line reading is absurt
char	*cub_map_read(int fd)
{
	char	*raw_map;
	char	*tmp;
	char	read_buffer[10000];
	int		bytes_read;

	raw_map = malloc(1);
	if (!raw_map)
		read_error("malloc() failed.", NULL, fd);
	raw_map[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, sizeof(read_buffer) -1);
		if (bytes_read == -1)
			read_error("read() failed.", raw_map, fd);
		read_buffer[bytes_read] = '\0';
		tmp = ft_strjoin(raw_map, read_buffer);
		if (!tmp)
			read_error("malloc() failed.", raw_map, fd);
		free(raw_map);
		raw_map = tmp;
	}
	return (raw_map);
}

static void	read_error(char *msg, char *raw_map, int fd)
{
	if (raw_map)
		free(raw_map);
	close(fd);
	cleanup(msg);
}