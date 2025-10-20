/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:41:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/20 21:18:20 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "../main/vector.h"

typedef struct s_player t_player;
typedef struct s_view	t_view;

typedef struct s_main	t_main; // forward dec

# define FOV 60.0
# define MOVE_SPEED 0.35
# define SENSITIVITY 1.0 

struct s_player
{
	t_vector	pos;
	double		dov; // direction of view
};

void	change_direction(t_main *g, int key);
void	change_position(t_main *g, int key);

#endif
