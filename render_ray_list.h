/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 04:27:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 04:37:53 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_RAYLIST_H
# define RENDER_RAYLIST_H

# include "render.h"

typedef struct s_ray_node	t_ray_node;
typedef struct s_ray_list	t_ray_list;

struct s_ray_node
{
	t_ray_node	*next;
	t_ray_node	*prev;
	t_ray		ray;
};

struct s_ray_list
{
	t_ray_node	*head;
	t_ray_node	*tail;
};

void	list_create(t_ray_list *raylist, int size);
void	list_add_left(t_ray_list *list, t_ray ray);
void	list_add_right(t_ray_list *list, t_ray ray);
void	list_pop_right(t_ray_list *list);
void	list_pop_left(t_ray_list *list);
void	list_clear(t_ray_list *list);

#endif