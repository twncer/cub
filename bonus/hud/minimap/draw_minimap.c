/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:15:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/31 02:47:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minimap.h"

void draw_minimap(t_main *game)
{
    int x = 1, y = 1, xx, yy, xx1, yy1;
    int gap = 0;
    int color = 0xff0000;
    
    while (y < MMAP_GRID_COUNT * (gap + 1))
    {
        while (x < MMAP_GRID_COUNT * (gap + 1))
        {
            yy1 = y * MMAP_GRID_SIZE; yy = yy1;
            xx1 = x * MMAP_GRID_SIZE; xx = xx1;

            while (yy < yy1 + MMAP_GRID_SIZE)
            {
                while (xx < xx1 + MMAP_GRID_SIZE)
                {
                    put_pixel(xx, yy, color, &game->window);
                    xx++;
                }
                xx = xx1;
                yy++;
            }
            x = x + gap + 1;
        }
        x = 1;
        y = y + gap + 1;
    }
}
