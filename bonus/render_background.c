/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:15:12 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/15 21:22:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	render_background(t_main *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (y < (WIN_HEIGHT / 2))
				put_pixel(x, y, g->map.color_c, &g->window);
			else
				put_pixel(x, y, g->map.color_f, &g->window);
		}
	}
}
