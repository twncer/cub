/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 06:39:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/20 20:42:32 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define KEY_D 100
# define KEY_A 97
# define KEY_W 119
# define KEY_S 115

# include "../map/map.h"
# include "window.h"
# include "../player/player.h"
# include "../render/render.h"
# include "../render/render_ray_list.h"

# include <stdbool.h>

typedef struct s_key_list t_key_list;
typedef struct s_main t_main;

struct s_key_list
{
	bool W;
	bool A;
	bool S;
	bool D;
};

struct s_main
{
	t_map		map;
	t_window	window;
	t_ray_list	rays;
	t_key_list	key_list;
};

#endif