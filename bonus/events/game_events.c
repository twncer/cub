/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:33:18 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/22 20:49:03 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h> // for debug

static void debug(t_main *game)
{
	char w, a, s, d, al, ar, e, q, spc;
	
	w = game->key_list.w ? 'W': ' ';
	a = game->key_list.a ? 'A': ' ';
	s = game->key_list.s ? 'S': ' ';
	d = game->key_list.d ? 'D': ' ';
	al = game->key_list.arrow_l ? '<': ' ';
	ar = game->key_list.arrow_r ? '>': ' ';
	e = game->key_list.e.key ? 'E': ' ';
	q = game->key_list.q.key ? 'Q': ' ';
	spc = game->key_list.spc.key ? '_': ' ';
	
	printf("\n\n\n  (%c)   (%c)   (%c)\n(%c)     (%c)     (%c)           (%c)  (%c)\n                       (%c)\n",
		q, w, e, a, s, d, al, ar, spc);
}

int terminate_hook(void)
{
	printf("dont kill me :c\n");
	exit(0);
	return (0);
}

int loop_event(t_main *game)
{
	cub_render(game);
	change_position(game, 0);
	change_direction(game, 0);
	unlock_switch(game);
    // debug(game);
	(void)debug;
	usleep(1000);
	return (0);
}
