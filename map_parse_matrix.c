/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:48:09 by yusudemi          #+#    #+#             */
/*   Updated: 2025/09/08 01:46:13 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdlib.h>
#include <stdio.h>

static int	flood_fill(char **matrix, int x, int y)
{
	int	up;
	int	down;
	int	left;
	int	right;

	if (y < 0 || !matrix[y] || x < 0 || matrix[y][x] == 0)
		return (0);
	if (matrix[y][x] == 2 || matrix[y][x] == 83)
		return (1);
	matrix[y][x] = 83;
	up = flood_fill(matrix, x, y - 1);
	down = flood_fill(matrix, x, y + 1);
	left = flood_fill(matrix, x - 1, y);
	right = flood_fill(matrix, x + 1, y);
	return (up && down && left && right);
}

static char	**copy_matrix(char **matrix, int height)
{
	char	**copy;
	int i;
	int j;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
			;
		copy[i] = malloc(sizeof(char) * (j + 1));
		if (!copy)
			return (NULL);
		j = -1;
		while (matrix[i][++j])
			copy[i][j] = matrix[i][j];
		copy[i][j] = 0;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_copy_matrix(char **copy)
{
	int l;

	l = -1;
	while (copy[++l])
		free(copy[l]);
	free(copy);
}

void	parse_matrix(char *raw_map, t_main *g)
{
	int 	matrix_height;
	char	**copy;
	
	if (!*raw_map)
	{
		printf("Error: Missing map data\n");
		exit(1);
	}
	matrix_height = create_matrix(raw_map, g);
	// copy current matrix to make changes on it
	copy = copy_matrix(g->map.matrix, matrix_height);
	if (!copy)
		map_cleanup_exit("Error: Memory allocation failed", g);
	// validate the matrix through copy
	if (!flood_fill(copy, g->map.player.x, g->map.player.y))
	{
		free_copy_matrix(copy);
		map_cleanup_exit("Error: Player area is not properly enclosed by walls", g);
	}
}
