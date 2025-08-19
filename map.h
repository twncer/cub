/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:32:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/19 03:42:41 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// map values must be double since double is more precise. (most math.h funcs use double)

#ifndef MAP_H
# define MAP_H

typedef struct s_map t_map;

struct s_map
{
	double	**data;
};

#endif
