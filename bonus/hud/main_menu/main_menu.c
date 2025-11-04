/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:50:08 by root              #+#    #+#             */
/*   Updated: 2025/11/04 16:39:13 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hud.h"
#include "../../main/main.h"

void *init_main_menu(t_main *g, t_main_menu *mmenu)
{
    mmenu->active = true;
    mmenu->bg_img = g->gallery.mmenu_bg;
    set_button(&mmenu->btn_start, true, &g->gallery.mmenu_start_btn,
        (t_vector){(WIN_WIDTH / 2 - g->gallery.mmenu_start_btn.width / 4), 310});
}

// void	render_main_menu(t_main *g)
// {	
// 	draw_image(&g->window, &g->gallery.mmenu_bg, 0, 0);
// 	draw_button(&g->window, &g->gallery.mmenu_start_btn, 0, 0);
// 	draw_button_hover(&g->window, &g->gallery.mmenu_start_btn, 0, g->gallery.mmenu_start_btn.height);
// 	mlx_put_image_to_window(g->window.mlx, g->window.win, g->window.img, 0, 0);
// }
