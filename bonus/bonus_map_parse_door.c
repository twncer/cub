/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_map_parse_door.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 04:21:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/29 00:20:00 by yusudemi         ###   ########.fr       */
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

static void	insert_inner_walls(t_door_wall *new)
{
	if (new->axis == 0) // horizontal
	{
		new->inner_wall_1.s.x = new->map_pos.x;
		new->inner_wall_1.s.y = new->map_pos.y + (1.0 - DOOR_WIDTH) / 2.0;
		new->inner_wall_1.e.x = new->map_pos.x + 1.0;
		new->inner_wall_1.e.y = new->map_pos.y + (1.0 - DOOR_WIDTH) / 2.0;
	
		new->inner_wall_2.s.x = new->map_pos.x;
		new->inner_wall_2.s.y = new->map_pos.y + 0.5 + (DOOR_WIDTH / 2.0);
		new->inner_wall_2.e.x = new->map_pos.x + 1.0;
		new->inner_wall_2.e.y = new->map_pos.y + 0.5 + (DOOR_WIDTH / 2.0);
	}
	else // door->axis == 1 // vertical
	{
		new->inner_wall_1.s.x = new->map_pos.x + (1.0 - DOOR_WIDTH) / 2.0;
		new->inner_wall_1.s.y = new->map_pos.y;
		new->inner_wall_1.e.x = new->map_pos.x + (1.0 - DOOR_WIDTH) / 2.0;
		new->inner_wall_1.e.y = new->map_pos.y + 1.0;
	
		new->inner_wall_2.s.x = new->map_pos.x + 0.5 + (DOOR_WIDTH / 2.0);
		new->inner_wall_2.s.y = new->map_pos.y;
		new->inner_wall_2.e.x = new->map_pos.x + 0.5 + (DOOR_WIDTH / 2.0);
		new->inner_wall_2.e.y = new->map_pos.y + 1.0;
	}
}
/*
static void	insert_door(t_door_wall *new)
{
	if (new->axis == 0) // horizontal
	{
		new->pos.s.x = new->map_pos.x + 0.5;
		new->pos.s.y = new->map_pos.y + (1.0 - DOOR_WIDTH) / 2.0;
		new->pos.e.x = new->pos.s.x;
		new->pos.e.y = new->pos.s.y + DOOR_WIDTH;
	}
	else // vertical
	{
		new->pos.s.x = new->map_pos.x + (1.0 - DOOR_WIDTH) / 2.0;
		new->pos.s.y = new->map_pos.y + 0.5;
		new->pos.e.x = new->pos.s.x + DOOR_WIDTH;
		new->pos.e.y = new->pos.s.y;
	}

}
*/
static void	new_door(int x, int y, int axis, t_door_wall *new)
{
	new->map_pos.x = x;
	new->map_pos.y = y;
	if (axis == 'd')
	{
		new->axis = 0;
	}
	else // axis == 'D'
	{
		new->axis = 1;
		
	}
	insert_inner_walls(new);
}

static t_door_wall *create_door_walls(char *raw_map, int count)
{
	t_door_wall	*door_walls;
	int		x;
	int		y;
	int		i;
	
	door_walls = malloc(sizeof(t_door_wall) * count); // gc add here
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
			new_door(x, y, *raw_map, &(door_walls[i++]));
			x++;
		}
		else
			x++;
		raw_map++;
	}
	return (door_walls);
}

void	parse_doors(char *raw_map)
{
	t_door_wall	*door_walls;

	int count = count_doors(raw_map);
	if (count == 0)
		return ;
	door_walls = create_door_walls(raw_map, count);
	find_door_wall(-1, count, door_walls);
}
