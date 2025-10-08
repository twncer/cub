/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:05:37 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 04:40:34 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_ray_list.h"
#include <stdlib.h>

static	void copy_ray(t_ray *dest, t_ray *src)
{
	dest->distance = src->distance;
	dest->hit.x = src->hit.x;
	dest->hit.y = src->hit.y;
	dest->side = src->side;
}

void	list_add_right(t_ray_list *list, t_ray ray)
{
	t_ray_node	*new;
	
	new = malloc(sizeof(t_ray_node));
	if (!new)
		return ;
	copy_ray(&(new->ray), &ray);
	new->next = NULL;
	new->prev = list->tail;
	if (list->tail)
		list->tail->next = new;
	else
		list->head = new;
	list->tail = new;
}

void		list_add_left(t_ray_list *list, t_ray ray)
{
	t_ray_node	*new;
	
	new = malloc(sizeof(t_ray_node));
	if (!new)
		return ;
	copy_ray(&(new->ray), &ray);
	new->next = list->head;
	new->prev = NULL;
	if (list->head)
		list->head->prev = new;
	else
		list->tail = new;
	list->head = new;
}

void		list_pop_right(t_ray_list *list)
{
	t_ray_node	*to_remove;

	if (!list->tail) // necessarry for when you get so high sensitivity
		return ;
	to_remove = list->tail;
	list->tail = to_remove->prev;
	
	if (list->tail)
		list->tail->next = NULL;
	else
		list->head = NULL;
	free(to_remove);
}

void		list_pop_left(t_ray_list *list)
{
	t_ray_node	*to_remove;

	if (!list->tail) // necessarry for when you get so high sensitivity
		return ;
	to_remove = list->head;
	list->head = to_remove->next;
	
	if (list->head)
		list->head->prev = NULL;
	else
		list->tail = NULL;
	free(to_remove);
}