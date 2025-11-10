/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/10 15:24:08 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "../minilibx/mlx_int.h"
#include <X11/Xlib.h>

#include <stdio.h>

void center_mouse(t_main *game)
{
    t_xvar *xvar;
    Display *display;     
    Window window_cub3d;

    xvar = (t_xvar *)game->window.mlx;
    display = xvar->display;
    window_cub3d = xvar->win_list->window;
    XWarpPointer(display, None, window_cub3d, 0, 0, 0, 0, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

t_vector get_mouse_position(t_main *game)
{
    t_xvar *xvar;
    Window cub3d;
    int win_x, win_y;
    unsigned int m;
    t_vector response;
    
    xvar = (t_xvar *)game->window.mlx;
    cub3d = xvar->win_list->window;
    XQueryPointer(xvar->display, cub3d, &cub3d, &cub3d, &win_x, &win_x, &win_x, &win_y, &m);
    response.x = win_x;
    response.y = win_y;
    return (response);
}

void read_mouse_movements(t_main *game)
{
    t_xvar *xvar;
    Window cub3d;
    int win_x, win_y;
    unsigned int m;
    int win_x_abs;
    
    xvar = (t_xvar *)game->window.mlx;
    cub3d = xvar->win_list->window;
    XQueryPointer(xvar->display, cub3d, &cub3d, &cub3d, &win_x, &win_x, &win_x, &win_y, &m);

    win_x_abs = win_x - WIN_WIDTH / 2;
    if (win_x_abs > 0)
        change_direction_advanced(game, 'R', win_x_abs);
    else if (win_x_abs < 0)
        change_direction_advanced(game, 'L', win_x_abs);
}

int mouse_click(int button, int x, int y, void *game)
{
    t_main *g;
    t_button *btn;
    
    g = game;
    if (g->main_menu.active)
    {
        btn = &g->main_menu.btn_start;
        if (x > btn->position.x && x < btn->position.x + btn->width)
            if (y > btn->position.y && y < btn->position.y + btn->height)
                activate_button(g, btn);
    }
    return (0);
}


// Bool XQueryPointer(
//     Display *display,          // X display bağlantısı
//     Window w,                  // Query yapılacak window
//     Window *root_return,       // Root window (OUT)
//     Window *child_return,      // Mouse'un üzerinde olduğu child window (OUT)
//     int *root_x, *root_y,      // Ekran (root) koordinatları (OUT)
//     int *win_x, *win_y,        // Window içi koordinatlar (OUT)
//     unsigned int *mask_return  // Mouse button ve modifier keys (OUT)
// );