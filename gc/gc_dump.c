/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_dump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:51:06 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/19 07:44:05 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "../minilibx/mlx.h"

static void dump_collector(t_gc *gc)
{
    t_garbage *node;
    t_garbage *node_to_free;
    
    if (gc->first_node)
        node = gc->first_node;
    else
    {
        if (gc)
            free(gc);
        return ;
    }
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

void dump_gc(void)
{
    dump_collector(get_gc());
}

void safe_mlx(void *ptr, int option)
{
    static void *mlx = NULL;
    static void *win = NULL;
    
    if (option == op_mlx)
        mlx = ptr;
    else if (option == op_win)
        win = ptr;
    else if (option == op_destroy)
    {
        (void)ptr;
        if (mlx && win)
            mlx_destroy_window(win, mlx);
        if (mlx)
            mlx_destroy_display(mlx);
        free(win);
        free(mlx);
        mlx = NULL;
        win = NULL;
    }
    else
        return ;
}

void dump_crit_gc(void)
{
    safe_mlx(NULL, op_destroy);
    dump_collector(get_crit_gc());
}
