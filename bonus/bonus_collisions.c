/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 05:47:05 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/30 05:54:08 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ideas:
// wall collisions -> normal wall - inner wall
// object collisions -> door - fireball(burak?)((make it last))
// need a raycasting like algorithm
// algo:: if player moves and collide to a wall find the hit point
// according to this hit point normalize the walk vector
// if there is no hitting to anywhere just walk