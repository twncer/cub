/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:41:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/01 17:55:51 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_player t_player;
typedef struct s_view	t_view;

# define FOV 60.0;

struct s_player
{
	double	x;
	double	y;
	double	view_ref_x;
	double	view_ref_y;
};

#endif
