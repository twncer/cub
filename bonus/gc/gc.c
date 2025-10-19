/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:03:40 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/16 14:38:25 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include <unistd.h>

void mem_err(void)
{
    write(1, "Memory error!\n", 14);
    exit(1);
}

void *alloc(ssize_t size)
{
    t_garbage *garbage;
    t_gc *gc;
    
    garbage = new_garbage();
    if (!garbage)
        mem_err();
    garbage->mem = malloc(size);
    if (!garbage->mem)
        mem_err();
    gc = get_gc();
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
    return (garbage->mem);
}

void *alloc_crit(ssize_t size)
{
    t_garbage *garbage;
    t_gc *gc;
    
    garbage = new_garbage();
    if (!garbage)
        mem_err();
    garbage->mem = malloc(size);
    if (!garbage->mem)
        mem_err();
    gc = get_crit_gc();
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
    return (garbage->mem);
}
