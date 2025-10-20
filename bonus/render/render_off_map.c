/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_off_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:24:13 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 10:30:50 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"

#include <stdio.h>
void	render_black_screen(t_window *win)
{
	int black;
	int	y;
	int x;

	printf("rendering the fucking black screen >&\n");
	black = 0x000000;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			put_pixel(x,y,black,win);
		}
	}
}

int check_off_map(t_main *g)
{
	double	width;
	double	height;

	if (g->map.player.pos.y < 0.0 || g->map.player.pos.x < 0.0)
		return (1);
	height = 0.0;
	while (g->map.matrix[(int)height])
		height += 1.0;
	if (g->map.player.pos.y >= height)
		return (1);
	width = 0.0;
	while (g->map.matrix[(int)g->map.player.pos.y][(int)width])
		width += 1.0;
	if (g->map.player.pos.x >= width)
		return (1);
	return (0);
}