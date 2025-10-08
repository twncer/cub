/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_put_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:54:18 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 03:54:30 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_pixel(int x, int y, int color, t_window *win)
{
	char	*dest;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dest = win->addr + (y * win->line_length + x
				* (win->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
}