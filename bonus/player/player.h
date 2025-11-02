/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:41:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/11/02 09:20:35 by yusudemi         ###   ########.fr       */
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
# define MOVE_MULT 0.05
# define SENSITIVITY 0.4
# define PLAYER_RADIUS 0.1

struct s_player
{
	t_vector	pos;
	double		dov; // direction of view
};

void	change_direction(t_main *g, int key);
void	change_position(t_main *g, int key);
void	change_direction_advanced(t_main *g, int direction, int weight);

t_vector	check_collision(t_main *g, t_vector movement);

#endif

// q, mouse2 -> next spell
// e -> interaction
// spc, mouse1 -> cast