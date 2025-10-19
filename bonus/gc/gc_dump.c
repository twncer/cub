/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:51:06 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/16 14:59:16 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void dump_gc(void)
{
    t_gc *gc;
    t_garbage *node;
    t_garbage *node_to_free;
    
    gc = get_gc();
    if (gc->first_node)
        node = gc->first_node;
    else
        return;
    while (node)
    {
        if (node->mem)
            free(node->mem);
        node_to_free = node;
        node = node->next;
        free(node_to_free);
    }
    free(gc);
}