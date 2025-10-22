/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_map_parse_door.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 04:21:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/22 20:26:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
// doors must parse before matrix!!
#include "main.h"
#include <stdlib.h>
#include <math.h>
// classic function count create parse!

static int	count_doors(char *raw_map)
{
	int ret;

	ret = 0;
	while (*raw_map)
	{
		if (*raw_map == 'd' || *raw_map == 'D')
			ret++;
		raw_map++;
	}
	return (ret);
}

static void	insert_inner_walls(t_door *new)
{
	if (new->axis == 0) // horizontal
	{
		new->inner_wall_1.s.x = new->pos.x;
		new->inner_wall_1.s.y = new->pos.y + 0.35;
		new->inner_wall_1.e.x = new->pos.x + 1;
		new->inner_wall_1.e.y = new->pos.y + 0.35;
	
		new->inner_wall_2.s.x = new->pos.x;
		new->inner_wall_2.s.y = new->pos.y + 0.65;
		new->inner_wall_2.e.x = new->pos.x + 1.0;
		new->inner_wall_2.e.y = new->pos.y + 0.65;
	}
	else // door->axis == 1 // vertical
	{
		new->inner_wall_1.s.x = new->pos.x + 0.35;
		new->inner_wall_1.s.y = new->pos.y;
		new->inner_wall_1.e.x = new->pos.x + 0.35;
		new->inner_wall_1.e.y = new->pos.y + 1.0;
	
		new->inner_wall_2.s.x = new->pos.x + 0.65;
		new->inner_wall_2.s.y = new->pos.y;
		new->inner_wall_2.e.x = new->pos.x + 0.65;
		new->inner_wall_2.e.y = new->pos.y + 1.0;
	}
}

static void	new_door(int x, int y, int axis, t_door *new)
{
	new->pos.x = x;
	new->pos.y = y;
	if (axis == 'd')
	{
		new->axis = 0;
		new->dov = M_PI;
	}
	else // axis == 'D'
	{
		new->axis = 1;
		new->dov = M_PI / 2;
		
	}
	new->state = LOCKED;
	insert_inner_walls(new);
}

static t_door *create_doors(char *raw_map, int count)
{
	t_door	*doors;
	int		x;
	int		y;
	int		i;
	
	doors = malloc(sizeof(t_door) * count); // gc add here
	x = 0;
	y = 0;
	i = 0;
	while (*raw_map)
	{
		if (*raw_map == '\n') // x = 0 y++
		{
			x = 0;
			y++;
		}
		else if (*raw_map == 'd' || *raw_map == 'D')
		{
			new_door(x, y, *raw_map, &(doors[i++]));
			x++;
		}
		else
			x++;
		raw_map++;
	}
	return (doors);
}

void	parse_doors(char *raw_map)
{
	t_door	*doors;

	int count = count_doors(raw_map);
	if (count == 0)
		return ;
	doors = create_doors(raw_map, count);
	find_door(-1, count, doors);
}
