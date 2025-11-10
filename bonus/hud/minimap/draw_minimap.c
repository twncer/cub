/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:15:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/08 06:41:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hud.h"
#include "../../main/main.h"
#include <math.h>

void draw_player_on_mmap(t_main *g)
{
    t_vector pos;
    int win_x;
    int win_y;
    double angle_deg;

    pos = g->map.player.pos;
    win_x = pos.x * 20;
    win_y = pos.y * 20;
    angle_deg = g->map.player.dov * 180.0 / M_PI + MMAP_PLAYER_IMAGE_OFFSET;
    draw_image_rotated(&g->window, &g->gallery.mmap.player, win_x, win_y, angle_deg);
}

void draw_mmap(t_main *g)
{
    int row;
    int col;
    int win_x;
    int win_y;

    row = MMAP_GRID_COUNT;
    win_x = 0;
    win_y = win_x;
    while (row--)
    {
        col = MMAP_GRID_COUNT;
        while (col--)
        {
            draw_image(&g->window, &g->gallery.mmap.floor, win_x, win_y);
            win_x += 20;
        }
        win_x = 0;
        win_y += 20;
    }
    draw_player_on_mmap(g);
}

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
