/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:15:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/28 02:23:54 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minimap.h"

void draw_minimap(t_main *game)
{
    int x = 1, y = 1, xx, yy, xx1, yy1;
    
    while (y < 15)
    {
        while (x < 15)
        {
            yy1 = y * 10; yy = yy1;
            xx1 = x * 10; xx = xx1;
            while (yy != yy1 + 10)
            {
                while (xx != xx1 + 10)
                {
                    put_pixel(xx, yy, 0x000000, &game->window);
                    xx++;
                }
                xx = xx1;
                yy++;
            }
            x++;
        }
        x = 1;
        y++;
    }
}
