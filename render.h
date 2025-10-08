/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:02:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 04:39:47 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "player.h"

typedef struct s_cast_data	t_cast_data;
typedef struct s_ray		t_ray;
typedef struct s_main		t_main;
typedef struct s_window		t_window;

struct s_cast_data
{
	t_ray			*ray;
	t_player		*player;
	t_vector_int	map_pos;
	t_vector		ray_d;
	t_vector_int	step;
	t_vector		side_dist;
	t_vector		delta_dist;
};

struct s_ray
{
	t_vector	hit;
	double		distance;
	char		side;
};

typedef void	(*t_raycasting_func)(t_main *g);

void	cub_render(t_main *g, t_raycasting_func raycasting);
void	put_pixel(int x, int y, int color, t_window *win);
void	render_background(t_main *g);
void	raycasting(t_main *g);
void	raycasting_right_rotation(t_main *g);
void	raycasting_left_rotation(t_main *g);
void	raycast_single(t_cast_data *d, char **matrix);

#endif