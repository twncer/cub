/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_gallery.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:59 by root              #+#    #+#             */
/*   Updated: 2025/11/08 05:52:24 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_images.h"

static void init_mmap_gallery(t_cub3_gallery *gal)
{
    gal->mmap.floor = create_image("cub3_images/images/minimap/floor.cub3");
    gal->mmap.wall = create_image("cub3_images/images/minimap/wall.cub3");
    gal->mmap.player = create_image("cub3_images/images/minimap/player.cub3");
}

void *init_gallery_with_config(t_cub3_gallery *gal, char *config)
{
    t_cub3_image img = create_image("cub3_images/images/main_menu.cub3");
    t_cub3_image img2 = create_image("cub3_images/images/main_menu_active.cub3");
    t_cub3_image img3 = create_image("cub3_images/images/main_menu_start_btn.cub3");

    (void)config;
    gal->mmenu_bg = img;
    gal->mmenu_bg_active = img2;
    gal->mmenu_start_btn = img3;
    init_mmap_gallery(gal);
    return (gal);
} // this is OK for TODO#1, not for the other
