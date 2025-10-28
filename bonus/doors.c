/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/28 02:26:44 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE // delete it later its just for me .p
#include "main.h"
#include <stddef.h>
#include <math.h>

#include <stdio.h>
t_door_wall	*find_door(int x, int y, t_door_wall *new)
{
	static t_door_wall *doors = NULL;
	static int count = 0;
	int	i;

	if (x == -1 && new)
	{
		count = y;
		doors = new;
		return (NULL);
	}
	i = -1;
	while (++i < count)
	{
		if (x == doors[i].map_pos.x && y == doors[i].map_pos.y)
			return (&doors[i]);
	}
	return (NULL);
}



// interact_door

