/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:02:04 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/28 02:10:18 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "player.h"
# include "map.h"

typedef struct s_ray		t_ray;
typedef struct s_main		t_main;
typedef struct s_window		t_window;

typedef struct s_cast_data	t_cast_data;
typedef struct s_render_data		t_render_data;
typedef struct s_intersection_data	t_intersection_data;

struct s_cast_data
{
	t_ray			*ray;
	t_player		*player;
	t_vector_int	map_pos;
	t_vector		ray_d;
	t_vector_int	step;
	t_vector		side_dist;
	t_vector		delta_dist;
	double			fov_rad;
	double			direction;
};

struct s_render_data
{
	t_texture	*wall_texture;
	int			wall_height;
	int			wall_start;
	int			wall_end;
	double		wall_hit;
	int			texture_x;
	int			texture_y;
	double		texture_step;
	double		texture_pos;
};

struct s_ray
{
	t_vector	hit;
	double		distance;
	double		raw_distance;	// Distance before fish-eye correction
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
int 	check_off_map(t_main *g);
void	render_black_screen(t_window *win);
void	render_scene(t_main *g);
int		insert_door_hit(t_cast_data *d, int player_location);
void	insert_vertical_hit(t_cast_data *d);
void	insert_horizontal_hit(t_cast_data *d);
int 	find_intersection(t_cast_data *d, t_segment inner_wall);

#endif