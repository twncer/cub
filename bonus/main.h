/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 06:39:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/24 16:29:01 by yusudemi         ###   ########.fr       */
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

typedef struct s_main t_main;

struct s_main
{
	t_map		map;
	t_window	window;
	t_ray_list	rays;
};

#endif