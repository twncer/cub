/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:22:49 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/16 14:31:03 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc *get_gc()
{
    static t_gc *gc = NULL;

    if (!gc)
    {
        gc = new_gc();
        if (!gc)
            mem_err();
    }
    return (gc);
}

t_gc *get_crit_gc()
{
    static t_gc *gc = NULL;

    if (!gc)
    {
        gc = new_gc();
        if (!gc)
            mem_err();
    }
    return (gc);
}