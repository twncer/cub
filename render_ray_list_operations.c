/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ray_list_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 21:05:37 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/12 02:36:20 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_ray_list.h"
#include <stdlib.h>


 // whenever pop right happens dont free the node add to left instead. go brr

void		list_pop_right(t_ray_list *list)
{
	t_ray_node	*to_move;

	if (!list->tail) // necessarry for when you get so high sensitivity
		return ;
	to_move = list->tail;
	list->tail = to_move->prev;
	if (list->tail)
		list->tail->next = NULL;
	else
		list->head = NULL;
	to_move->prev = NULL;
	to_move->next = list->head;
	if (list->head)
		list->head->prev = to_move;
	else
		list->tail = to_move;
	list->head = to_move;
}

void		list_pop_left(t_ray_list *list)
{
	t_ray_node	*to_move;

	if (!list->head) // necessarry for when you get so high sensitivity
		return ;
	to_move = list->head;
	list->head = to_move->next;
	if (list->head)
		list->head->prev = NULL;
	else
		list->tail = NULL;
	to_move->next = NULL;
	to_move->prev = list->tail;
	if (list->tail)
		list->tail->next = to_move;
	else
		list->head = to_move;
	list->tail = to_move;
}