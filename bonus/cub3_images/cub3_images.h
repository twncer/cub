/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_images.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:11:18 by root              #+#    #+#             */
/*   Updated: 2025/10/31 06:08:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_IMAGES_H
# define CUB3_IMAGES_H
# define BUFFER_SIZE 84
# define BIT_PER_PIXEL 3
# define RGB_FORMAT "RGB888"

# include <fcntl.h>
# include "../gc/gc.h"

typedef struct s_cub3_image t_cub3_image;
typedef struct s_cub3_scene t_cub3_scene;
typedef struct s_window t_window;

struct s_cub3_image
{
    int *image;
    int width;
    int height;
};

struct s_cub3_scene
{
    int id;
    t_cub3_image scene_bg;
};

t_cub3_image create_image(char *path);
void draw_image(t_window *win, t_cub3_image *img, int x, int y);

#endif