/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_cons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:08:13 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/19 04:56:23 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_garbage *new_garbage(ssize_t size)
{
    t_garbage *garbage;

    garbage = malloc(sizeof(t_garbage));
    if (!garbage)
        return (NULL);
    garbage->mem = malloc(size);
    if (!garbage->mem)
    {
        free(garbage);
        return (NULL);
    }
    garbage->next = NULL;
    return (garbage);
}

t_gc *new_gc(void)
{
    t_gc *gc;

    gc = malloc(sizeof(t_gc));
    if (!gc)
        return (NULL);
    gc->first_node = NULL;
    return (gc);
}
