/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_images.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:11:18 by root              #+#    #+#             */
/*   Updated: 2025/11/08 06:31:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_IMAGES_H
# define CUB3_IMAGES_H
# define BUFFER_SIZE 84
# define BIT_PER_PIXEL 3
# define RGB_FORMAT "RGB888"
# define CONTINUE 0
# define RESET 1

# include <fcntl.h>
# include "../gc/gc.h"

typedef struct s_cub3_image t_cub3_image;
typedef struct s_minimap_gallery t_mmap_gallery;
typedef struct s_cub3_gallery t_cub3_gallery;
typedef struct s_window t_window;

typedef t_cub3_image t_im;

struct s_cub3_image
{
    int *image;
    int width;
    int height;
};

struct s_minimap_gallery
{
    t_im floor;
    t_im wall;
    t_im player;
};

struct s_cub3_gallery
{
    t_im mmenu_bg;
    t_im mmenu_bg_active;
    t_im mmenu_start_btn;
    t_mmap_gallery mmap;
};

t_cub3_image create_image(char *path);
void draw_image(t_window *win, t_cub3_image *img, int x, int y);
void draw_image_rotated(t_window *win, t_cub3_image *img, int x, int y, double angle_deg); // claude
void draw_button(t_window *win, t_cub3_image *img, int x, int y);
void draw_button_hover(t_window *win, t_cub3_image *img, int x, int y);

void *init_gallery_with_config(t_cub3_gallery *gal, char *config);

#endif