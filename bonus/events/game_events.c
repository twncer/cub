/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:33:18 by btuncer           #+#    #+#             */
/*   Updated: 2025/11/10 15:01:06 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <stdio.h> // for debug

int terminate_hook(void)
{
	printf("dont kill me :c\n");
	exit(0);
	return (0);
}

static int loop_main_menu(t_main *game)
{
	cub_render(game);
	// check_button;
	return (0);	
}

static int loop_game(t_main *game)
{
	cub_render(game);
	change_position(game, 0);
	change_direction(game, 0);
	
	if (game->key_list.f3.key_switch)
	{
		read_mouse_movements(game);
		center_mouse(game);
	}
	
	unlock_switch(game);
	usleep(1000);
	return (0);	
}

int loop_event(t_main *game)
{
	if (game->main_menu.active)
		return (loop_main_menu(game));
	else
		return (loop_game(game));
}
