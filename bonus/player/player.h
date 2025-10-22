/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:41:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/22 18:26:42 by btuncer          ###   ########.fr       */
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
# define SENSITIVITY 0.4

struct s_player
{
	t_vector	pos;
	double		dov; // direction of view
};

void	change_direction(t_main *g, int key);
void	change_position(t_main *g, int key);

#endif

// q, mouse2 -> next spell
// e -> interaction
// spc, mouse1 -> cast