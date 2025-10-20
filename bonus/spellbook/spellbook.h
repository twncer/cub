/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spellbook.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:10:39 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/20 20:12:31 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_pos t_pos;
typedef struct s_fireball t_fireball;

struct s_pos
{
    int x;
    int y;
};

struct s_fireball
{
    int id;
    t_pos pos;
};
