/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:50:08 by root              #+#    #+#             */
/*   Updated: 2025/11/03 06:08:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hud.h"
#include "../../main/main.h"

void *init_main_menu(t_main *g, t_main_menu *mmenu)
{
    mmenu->bg_img = g->gallery.mmenu_bg;
    set_button(&mmenu->btn_start, true, &g->gallery.mmenu_start_btn,
        (t_vector){0, 0});
}