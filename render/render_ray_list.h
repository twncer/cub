/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 04:27:51 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/15 21:22:23 by root             ###   ########.fr       */
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