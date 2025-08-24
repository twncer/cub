/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 07:25:00 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 09:05:09 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "main.h"
#include "minilibx/mlx.h"
#include <stdio.h>

static t_texture	*find_target_texture(int id)
{
	t_map	*map;
	t_texture	*target;

	map = &(pointer_storage(NULL)->map_datas);
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

void	map_parse_texture(int id, char *relative_path, int ext)
{
	void	*mlx;
	t_texture *target_texture;

	mlx = pointer_storage(NULL)->window.mlx;
	target_texture = find_target_texture(id);
	if (ext == 0)
		target_texture->img = mlx_xpm_file_to_image(mlx, relative_path, 
			&target_texture->width, &target_texture->height);
	else if (ext == 1)
		target_texture->img = mlx_png_file_to_image(mlx, relative_path, 
			&target_texture->width, &target_texture->height);
	free(relative_path);
	if (!target_texture->img)
		cleanup("Failed to load texture image");
	target_texture->addr = mlx_get_data_addr(target_texture->img,
		&target_texture->bits_per_pixel, &target_texture->line_length,
		&target_texture->endian);
	if (!target_texture->addr)
		cleanup("Failed to get texture data address");
}
