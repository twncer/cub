/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:51:08 by root              #+#    #+#             */
/*   Updated: 2025/11/10 17:57:46 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MMAP_GRID_SIZE 20
# define MMAP_GRID_COUNT 11
# define MMAP_RANGE 7

# define MMAP_MARGIN 20

# define MMAP_PLAYER_IMAGE_OFFSET 90.0

# include "../minilibx/mlx.h"
# include "../cub3_images/cub3_images.h"
# include "../main/vector.h"
# include <stdbool.h>

typedef struct s_button t_button;
typedef struct s_main_menu t_main_menu;
typedef struct s_main t_main;
typedef struct s_pos t_pos;

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

struct s_pos
{
    int x;
    int y;
};

void draw_minimap(t_main *game);
void draw_mmap(t_main *g);

void *init_main_menu(t_main *g, t_main_menu *mmenu);

void *set_button(t_button *button, bool hover, t_im *img, t_vector pos);
void check_button(t_main *game, t_button *button);
void place_button(t_main *g, t_button *btn);
void activate_button(t_main *g, t_button *btn);

#endif