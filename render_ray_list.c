/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:05:00 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/12 02:37:16 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_ray_list.h"
#include <stdlib.h>
#include <string.h>
#include "window.h"

static t_ray	*create_ray_pack(int size)
{
	t_ray	*pack;

	pack = malloc(sizeof(t_ray) * size);
	memset(pack, 0, sizeof(t_ray) * size);
	return (pack);
}

static void	add_ray_pack(t_ray_list *list, t_ray *ray_pack)
{
	t_ray_node	*new;
	
	new = malloc(sizeof(t_ray_node));
	if (!new)
		return ;
	new->ray_pack = ray_pack;
	new->next = NULL;
	new->prev = list->tail;
	if (list->tail)
		list->tail->next = new;
	else
		list->head = new;
	list->tail = new;
}

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
		add_ray_pack(raylist, empty);
	}
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
		curr->ray_pack = NULL;
		free(curr);
		curr = next;
	}
	list->head = NULL;
	list->tail = NULL;
}
