/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:15:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/10 18:08:22 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hud.h"
#include "../../main/main.h"
#include <math.h>

static void draw_player_on_mmap(t_main *g)
{
    t_vector pos;
    int win_x;
    int win_y;
    double angle_deg;

    pos = g->map.player.pos;
    win_x = (MMAP_GRID_COUNT / 2 + 1) * MMAP_GRID_SIZE; // margin eklenecek
    win_y = win_x;
    angle_deg = g->map.player.dov * 180.0 / M_PI + MMAP_PLAYER_IMAGE_OFFSET;
    draw_image_rotated(&g->window, &g->gallery.mmap.player, win_x, win_y, angle_deg);
}

static void draw_floors(t_main *g)
{
    int row;
    int col;
    int win_x;
    int win_y;

    row = MMAP_GRID_COUNT;
    win_x = MMAP_MARGIN;
    win_y = MMAP_MARGIN;
    while (row--)
    {
        col = MMAP_GRID_COUNT;
        while (col--)
        {
            draw_image(&g->window, &g->gallery.mmap.floor, win_x, win_y);
            win_x += MMAP_GRID_SIZE;
        }
        win_x = MMAP_GRID_SIZE;
        win_y += MMAP_GRID_SIZE;
    }  
}

static void draw_walls(t_main *g)
{
    t_vector pp;
    t_vector counter;
    t_vector curr_pos;
    
    pp = (t_vector){g->map.player.pos.x, g->map.player.pos.y};
    counter = (t_vector){MMAP_RANGE, MMAP_RANGE};
    curr_pos = (t_vector){pp.x - 2.0, pp.y - 2.0};
    
    while ((counter.y)--)
    {
        if (curr_pos.y < 0)
        {
            curr_pos.y++;
            continue;
        }
        else if (g->map.matrix[(int)curr_pos.y] == NULL)
            break;
             
        while ((counter.x)--)
        {
            if (g->map.matrix[(int)curr_pos.y][(int)curr_pos.x] == NULL || g->map.matrix[(int)curr_pos.y][(int)curr_pos.x] != '1')
            {
                curr_pos.x++;
                continue;
            }
            draw_image(&g->window, &g->gallery.mmap.wall,
                (MMAP_GRID_COUNT / 2 + 1 + MMAP_RANGE / 2 + 1 - counter.x) * MMAP_GRID_SIZE,
                (MMAP_GRID_COUNT / 2 + 1 + MMAP_RANGE / 2 + 1 - counter.y) * MMAP_GRID_SIZE
            );
            curr_pos.x++;
        }
        counter.x = MMAP_RANGE;
        curr_pos.x = pp.x - 2.0;
        curr_pos.y++;
    }
}

void draw_mmap(t_main *g)
{
    draw_floors(g);
    draw_walls(g);
    draw_player_on_mmap(g);
}

// 1 2 3 4 5 6 -7- 8 9

// curr + range - cnt;

// curr = 7;
// range = 5;
// cnt = 5;
// wanted = 5;

// curr - ((cnt - 1) / 2)
// 7 - 2 | cnt 5 (2)
// 7 - 1 | cnt 4 (1)
// 7 - 0 | cnt 3 (0)
// 7 - () | cnt 2