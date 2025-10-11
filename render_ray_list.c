/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:05:00 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/11 19:23:04 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_ray_list.h"
#include <stdlib.h>
#include <string.h>
#include "window.h"

void	list_create(t_ray_list *raylist, int packege_size)
{
	t_ray	*empty;
	int		i;

	i = -1;
	raylist->package_size = packege_size;
	raylist->list_size = WIN_WIDTH / packege_size;
	while (++i < raylist->list_size)
	{
		empty = create_ray_pack(packege_size);
		list_add_right(raylist, empty);
	}
}

t_ray	*create_ray_pack(int size)
{
	t_ray	*pack;

	pack = malloc(sizeof(t_ray) * size);
	memset(pack, 0, sizeof(t_ray) * size);
	return (pack);
}

void	list_clear(t_ray_list *list)
{
	t_ray_node	*curr;
	t_ray_node	*next;

	curr = list->head;
	while (curr)
	{
		next = curr->next;
		free(curr->ray_pack);
		free(curr);
		curr = next;
	}
	list->head = NULL;
	list->tail = NULL;
}
