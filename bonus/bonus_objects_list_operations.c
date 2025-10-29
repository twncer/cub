/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects_list_operations.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:26:36 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/29 04:54:55 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stddef.h>

void	add_object(t_obj_list *list, int type, void *obj)
{
	t_obj_node *new;

	new = malloc(sizeof(t_obj_node)); // alloc_crit
	new->type = type;
	new->object = obj;
	new->next = NULL;
	new->next_render = NULL;
	new->next = list->all;
	list->all = new;
}

void	add_to_render_queue(t_obj_list *list, t_obj_node *node, double distance)
{
	t_obj_node	*curr;
	t_obj_node	*prev;

	node->distance = distance;
	node->next_render = NULL;
	if (!list->to_render || distance > list->to_render->distance)
	{
		node->next_render = list->to_render;
		list->to_render = node;
		return ;
	}
	prev = NULL;
	curr = list->to_render;
	while (curr && curr->distance >= distance)
	{
		prev = curr;
		curr = curr->next_render;
	}
	node->next_render = curr;
	prev->next_render = node;
}

void	clear_render_queue(t_obj_list *list)
{
	t_obj_node *curr;
	t_obj_node *next;

	curr = list->to_render;
	while (curr)
	{
		next = curr->next_render;
		curr->next_render = NULL;
		curr->distance = -1.0;
		curr = next;
	}
	list->to_render = NULL;
}
