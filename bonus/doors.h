/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:26:34 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 05:00:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOORS_H
# define DOORS_H

# include "vector.h"

typedef struct s_door	t_door;

// if door hit a player while closing it opens ig

enum e_door_states
{
	OPEN = 11,
	CLOSE, // also unlocked
	LOCKED,
	BURNING,
	DESTROYED
};

struct s_door
{
	t_vector_int	pos;
	double			dov; // this is not the dov of block its dov of the door vector (start to end)
	int				axis; // 0 -> horizontal [d on map], 1 -> vertical [D on map]
	int				state;
};

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