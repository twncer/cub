/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 04:27:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/12 02:37:22 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_RAYLIST_H
# define RENDER_RAYLIST_H

# include "render.h"

typedef struct s_ray_node	t_ray_node;
typedef struct s_ray_list	t_ray_list;

// todos for better performance
// make t_ray -> *t_ray. it become an array of rays
// one node takes (SENSITIVITY * 0.05(maybe define this) * WIN_WIDTH) + 1 ray
// this way you can free only one node and alloc one node per rotate
// on render you should refactor the algo if you make changes
// HAHAHA
// OK
struct s_ray_node
{
	t_ray_node	*next;
	t_ray_node	*prev;
	t_ray		*ray_pack; // this hold SENSITIVITY * 0.05 * WIN_WIDTH num of ray
};

struct s_ray_list
{
	t_ray_node	*head;
	t_ray_node	*tail;
	int			package_size;
	int			list_size;
};

void	list_create(t_ray_list *raylist, int packege_size);
void	list_clear(t_ray_list *raylist);
void	list_pop_right(t_ray_list *raylist);
void	list_pop_left(t_ray_list *raylist);

#endif