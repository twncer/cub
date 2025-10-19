/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_map_parse_door.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 04:21:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 10:02:10 by yusudemi         ###   ########.fr       */
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
t_door	*find_door(int x, int y, t_door *new);
#include <stdio.h>
void	parse_doors(char *raw_map)
{
	t_door	*doors;

	int count = count_doors(raw_map);
	if (count == 0)
		return ;
	doors = create_doors(raw_map, count);
	find_door(-1, count, doors);
}
