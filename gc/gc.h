/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:04:00 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/19 07:41:32 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>

enum e_safe_mlx_options
{
    op_mlx = 1,
    op_win,
    op_destroy
};

typedef struct s_garbage t_garbage;
typedef struct s_gc t_gc;

struct s_garbage
{
    void *mem;
    t_garbage *next;
};

struct s_gc
{
    t_garbage *first_node;
    t_garbage *last_node;
};

t_garbage *new_garbage(ssize_t size);
t_gc *new_gc(void);

t_gc *get_gc();
t_gc *get_crit_gc();

void *insert_to_gc(t_garbage *garbage, t_gc *gc);

void mem_err(void);

void *alloc(ssize_t size);
void *alloc_crit(ssize_t size);

void dump_gc(void);
void dump_crit_gc(void);

void safe_mlx(void *ptr, int option);

#endif