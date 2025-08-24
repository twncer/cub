/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 06:39:23 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 08:57:21 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "map.h"
# include "window.h"
# include "player.h"

typedef struct s_main t_main;

struct s_main
{
	t_map		map_datas;
	t_window	window;
	t_player	player;
};

void	cleanup(const char *msg);
t_main	*pointer_storage(t_main	*game);

#endif