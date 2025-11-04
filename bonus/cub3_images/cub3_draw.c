/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 05:39:18 by root              #+#    #+#             */
/*   Updated: 2025/11/03 06:22:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_images.h"

void draw_image(t_window *win, t_cub3_image *img, int x, int y)
{
    int x1;
    int y1;
    int counter;

    x1 = 0;
    y1 = 0;
    counter = 0;
    while (counter < (img->height * img->width))
    {
        if (counter != 0 && counter % img->width == 0)
        {
            x1 = 0;
            y1 = y1 + 1;
        }
        if (((unsigned int)img->image[counter]) != 0xffffffff)
            put_pixel(x1 + x, y1 + y, img->image[counter], win);
        x1++;
        counter++;
    }
}

void draw_button(t_window *win, t_cub3_image *img, int x, int y)
{
    int x1;
    int y1;
    int counter;

    x1 = 0;
    y1 = 0;
    counter = 0;
    while (counter < img->height * img->width)
    {
        if (counter != 0 && counter % img->width == 0)
        {
            x1 = 0;
            y1 = y1 + 1;
        }
        if (((unsigned int)img->image[counter]) != 0xffffffff)
            put_pixel(x1 + x, y1 + y, img->image[counter], win);
        x1++;
        counter++;
    }
}
