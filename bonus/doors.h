/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:34 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/24 03:55:54 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

# include "vector.h"


# define DOOR_SPEED 1.0;

typedef struct s_door_wall	t_door_wall;

// if door hit a player while closing it opens ig
// while opening or closing the door make you are casting a spell
// so you cant FUCKING MOVE
// problem solved
// when pressing e to open the door respect the fucking animation and dont move
// make wall collisions before the animation !!
// for the animation real time needed merge point XD
enum e_door_states
{
	OPEN = 11,
	CLOSE, // also unlocked
	LOCKED,
	BURNING,
	DESTROYED,
	OPENING,
	CLOSING
};

struct s_door_wall
{
	int				state;
	t_vector_int	map_pos;
	t_segment		inner_wall_1; // the wall inside the wall
	t_segment		inner_wall_2;
	int				axis; // 0 -> horizontal [d on map], 1 -> vertical [D on map]
	double			angle; // this is not the dov of block its dov of the door vector (start to end)
	double			target_angle;
	t_segment		pos;
};

t_door_wall	*find_door(int x, int y, t_door_wall *new);

/*
door on map
111111
100001
111611
1000N1
111111

on render


*/

#endif