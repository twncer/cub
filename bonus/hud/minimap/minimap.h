/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:16:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/28 18:36:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# define MMAP_GRID_SIZE 16
# define MMAP_EXPANDED_GRID_SIZE 32
# define MMAP_GRID_COUNT 10

# include "../../minilibx/mlx.h"
# include "../../main/main.h"

void draw_minimap(t_main *game);

#endif