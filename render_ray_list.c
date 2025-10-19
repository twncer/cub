/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:05:00 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 09:21:49 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_ray_list.h"
#include <stdlib.h>
#include <string.h>
#include "window.h"
#include <math.h>

#include "gc/gc.h"

#include <stdio.h>

static int	calculate_package_size(int target_size)
{
	int	i;
	int	best_size;
	int	best_diff;

	i = 0;
	best_size = 1;
	best_diff = abs(1 - target_size);
	while (++i < WIN_WIDTH)
	{
		if (WIN_WIDTH % i == 0)
		{
			if (abs(i - target_size) < best_diff)
			{
				best_diff = abs(i - target_size);
				best_size = i;
			}			
			if (i != (WIN_WIDTH / i) &&
				(abs(WIN_WIDTH / i - target_size) < best_diff))
			{
					best_diff = abs(WIN_WIDTH / i - target_size);
					best_size = WIN_WIDTH / i;
			}
		}
	}
	printf("targetsize::%d\nbest_size::%d\n", target_size, best_size);
	return (best_size);
}

static t_ray	*create_ray_pack(int size)
{
	t_ray	*pack;

	pack = alloc_crit(sizeof(t_ray) * size);
	memset(pack, 0, sizeof(t_ray) * size);
	return (pack);
}

static void	add_ray_pack(t_ray_list *list, t_ray *ray_pack)
{
	t_ray_node	*new;
	
	new = alloc_crit(sizeof(t_ray_node));
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
	packege_size = calculate_package_size(packege_size);
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
		// free(curr->ray_pack); HERE1
		curr->ray_pack = NULL;
		// free(curr); HERE1
		curr = next;
	}
	list->head = NULL;
	list->tail = NULL;
}
