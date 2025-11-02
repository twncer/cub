/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 06:39:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/02 09:08:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../map/map.h"
# include "window.h"
# include "../player/player.h"
# include "../render/render.h"
# include "../render/render_ray_list.h"
# include "../cub3_images/cub3_images.h"
# include "../objects/doors.h"
# include "../objects/bonus_objects.h"
# include "../objects/bonus_fireball.h"

# include <stdbool.h>

typedef struct s_key_list t_key_list;
typedef struct s_main t_main;
typedef struct s_switch_key t_switch_key;

struct s_switch_key
{
	int key;
	int key_switch;
};

struct s_key_list
{
	bool w;
	bool a;
	bool s;
	bool d;
	int arrow_l;
	int arrow_r;
	t_switch_key e;
	t_switch_key q;
	t_switch_key spc;
	t_switch_key f3;
};

struct s_main
{
	t_map		map;
	t_window	window;
	t_ray_list	rays;
	t_obj_list	objects;
	t_key_list	key_list;
	t_cub3_image img;
};

void	__init__(t_main *game);
void _init_hooks(t_main *game);

#endif