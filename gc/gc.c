/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:03:40 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/19 07:27:30 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include <unistd.h>

void mem_err(void)
{
    write(1, "Memory error!\n", 14);
    exit(1);
}

void *insert_to_gc(t_garbage *garbage, t_gc *gc)
{
    if (!garbage | !gc)
        return (NULL);
    if (!gc->first_node)
    {
        gc->first_node = garbage;
        gc->last_node = gc->first_node;
    }
    else
    {
        gc->last_node->next = garbage;
        gc->last_node = gc->last_node->next;
    }
    return (gc);
}

void *alloc(ssize_t size)
{
    t_garbage *garbage;

    garbage = new_garbage(size);
    if (!garbage || !insert_to_gc(garbage, get_gc()))
        mem_err();
    return (garbage->mem);
}

void *alloc_crit(ssize_t size) //   the first two garbages in crit gc are...
{                              // always 1) mlx connection and 2) window
    t_garbage *garbage;
    
    garbage = new_garbage(size);
    if (!garbage || insert_to_gc(garbage, get_crit_gc()))
        mem_err();
    return (garbage->mem);
}
