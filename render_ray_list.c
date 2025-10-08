/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:05:00 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 04:40:26 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_ray_list.h"
#include <stdlib.h>

void	list_create(t_ray_list *raylist, int size)
{
	t_ray		empty;
	int			i;

	empty.hit.x = 0.0;
	empty.hit.y = 0.0;
	empty.distance = 0.0;
	empty.side = 0;
	i = -1;
	while (++i < size)
		list_add_right(raylist, empty);
}

void	list_clear(t_ray_list *list)
{
	t_ray_node	*curr;
	t_ray_node	*next;

	curr = list->head;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	list->head = NULL;
	list->tail = NULL;
}
