/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 09:57:16 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stddef.h>

#include <stdio.h>
t_door	*find_door(int x, int y, t_door *new)
{
	static t_door *doors = NULL;
	static int count = 0;
	int	i;

	printf("dsadsa\n");
	if (x == -1 && new)
	{
		count = y;
		doors = new;
		return (NULL);
	}
	i = -1;
	printf("count::%d\n", count);
	while (++i < count)
	{
		printf("x::%dy::%d\n", x, y);
		printf("x::%dy::%d\n", doors[i].pos.x , doors[i].pos.y);
		if (x == doors[i].pos.x && y == doors[i].pos.y)
			return (&doors[i]);
	}
	return (NULL);
}
