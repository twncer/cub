/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_gallery.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:00:59 by root              #+#    #+#             */
/*   Updated: 2025/11/03 06:07:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_images.h"

void *init_gallery_with_config(t_cub3_gallery *gal, char *config)
{
    t_cub3_image img = create_image("cub3_images/images/main_menu.cub3");
    t_cub3_image img2 = create_image("cub3_images/images/main_menu_active.cub3");
    t_cub3_image img3 = create_image("cub3_images/images/main_menu_start_btn.cub3");

    (void)config;
    gal->mmenu_bg = img;
    gal->mmenu_bg_active = img2;
    gal->mmenu_start_btn = img3;
    return (gal);
}
