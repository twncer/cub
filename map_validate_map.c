/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:48:09 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 11:44:53 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "main.h"
#include <stdlib.h>

void	validate_map(char *raw_map)
{
	int	**map;
	int	map_height;

	if (!*raw_map)
		cleanup("Missing map data");
	map = create_matrix(raw_map);

}
