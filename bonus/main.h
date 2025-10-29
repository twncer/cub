/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 06:39:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/29 01:51:40 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "map.h"
# include "window.h"
# include "player.h"
# include "render.h"
# include "render_ray_list.h"
# include "doors.h"
# include "bonus_objects.h"
# include "gc/gc.h"
# include "bonus_fireball.h"

typedef struct s_main t_main;

struct s_main
{
	t_map		map;
	t_window	window;
	t_ray_list	rays;
	t_obj_list	objects;
};

#endif