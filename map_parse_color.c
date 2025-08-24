/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 07:11:09 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 09:04:58 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "main.h"
#include "minilibx/mlx.h"
#include <stdio.h>

void	map_parse_color(int rgb, int id)
{
	t_map	*map;

	map = &(pointer_storage(NULL)->map_datas);
	if (id == C)
		map->color_c = rgb;
	else if (id == F)
		map->color_f = rgb;
}
