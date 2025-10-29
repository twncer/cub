/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_fireball.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 22:32:13 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/29 02:06:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
casting
	when checking need to create a fireball segment according to player->dov
		this segment's length is according to u
		segment's angle is right to player->dov
	also according to player->dov init side data
	use check intersection function to find hit and distance of fireball ray
	after using intersection function check if ray is in player's sight
	if it is insert the index according to direction and player->dov
rendering
	check if current rendering part of screen == index
	if so check the currennt rendering part's ray distance and compare it with fireball_ray->distance
	put the fireball texture after wall
*/

#include "vector.h"

# define NUM_OF_FIREBALLS 5

typedef struct s_fireball	t_fireball;
// while rendering the fireball
// calculate fireball segment **
// calculate fireball tail segment **
// find the intersection and print
struct	s_fireball
{
	t_vector	position;
	double		direction;
};
