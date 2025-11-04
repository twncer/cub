/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:51:08 by root              #+#    #+#             */
/*   Updated: 2025/11/04 17:03:24 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MMAP_GRID_SIZE 16
# define MMAP_EXPANDED_GRID_SIZE 32
# define MMAP_GRID_COUNT 10

# include "../minilibx/mlx.h"
# include "../cub3_images/cub3_images.h"
# include "../main/vector.h"
# include <stdbool.h>

typedef struct s_button t_button;
typedef struct s_main_menu t_main_menu;
typedef struct s_main t_main;

struct s_button
{
    bool hover;
    t_im image;
    t_vector position;
    int width;
    int height;
    bool active;
};

struct s_main_menu
{
    bool active;
    t_cub3_image bg_img;
    t_button btn_start;
    t_button btn_exit;
};

void draw_minimap(t_main *game);

void *init_main_menu(t_main *g, t_main_menu *mmenu);

void *set_button(t_button *button, bool hover, t_im *img, t_vector pos);
void check_button(t_main *game, t_button *button);
void place_button(t_main *g, t_button *btn);
void activate_button(t_main *g, t_button *btn);

#endif