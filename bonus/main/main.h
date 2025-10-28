/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 06:39:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/28 00:06:37 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../map/map.h"
# include "window.h"
# include "../player/player.h"
# include "../render/render.h"
# include "../render/render_ray_list.h"

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
	t_key_list	key_list;
};

void	__init__(t_main *game);
void _init_hooks(t_main *game);

#endif