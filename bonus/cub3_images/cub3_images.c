/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:19:16 by root              #+#    #+#             */
/*   Updated: 2025/11/03 06:03:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_images.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>

static int init_cub3_image(t_cub3_image *img, char *first_line)
{
    char **attr;
    
    if (!first_line || !*first_line || ft_strlen(first_line) < 9)
        return (0);
    attr = ft_split(first_line, ':');
    if (!attr[2] || !attr[2][0])
        return (0);
    img->width = ft_atoi(attr[1]);
    img->height = ft_atoi(attr[2]);
    if (!(img->width) || !(img->height))
        return (0);
    return (1);
}

static int write_line_to_image(char *line, t_cub3_image *img, int stat)
{
    static int counter = 0;
    int line_counter;
    char **parsed_line;

    if (stat == RESET)
    {
        counter = 0;
        return (RESET);
    }
    parsed_line = ft_split(line, '.');
    line_counter = 0;
    while (parsed_line[line_counter])
    {
        img->image[counter] = (int)strtol(parsed_line[line_counter], NULL, 16);
        counter++;
        line_counter++;
    }
    return (1);
}

static int read_cub3_image_content(t_cub3_image *img, FILE *file)
{
    char *line;
    size_t buffer_size;
    int line_counter;
    
    img->image = alloc_crit(img->height * img->width * sizeof(int));
    line = NULL;
    buffer_size = BUFFER_SIZE;
    line_counter = img->height;
    while (line_counter--)
    {
        if (getline(&line, &buffer_size, file) < 8)
            return (0);
        write_line_to_image(line, img, CONTINUE);
    }
    write_line_to_image(NULL, NULL, RESET);
    return (1);
}

t_cub3_image create_image(char *path)
{
    FILE *file;
    char *line;
    size_t buffer_size;
    t_cub3_image new_image;
    t_cub3_image empty = {NULL, 0, 0};

    file = fopen(path, "r");
    if (!file)
        return (printf("err: cub3_image missing\n"), empty);
    line = NULL;
    buffer_size = BUFFER_SIZE;
    getline(&line, &buffer_size, file);
    if (!init_cub3_image(&new_image, line))
        return (printf("err: Wrong type of input\n"), empty);
    if (!read_cub3_image_content(&new_image, file))
        return (printf("err: Wrong type of input\n"), empty);
    fclose(file);
    free(line);
    return (new_image);
}
