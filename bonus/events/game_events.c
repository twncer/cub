/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:33:18 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/31 06:13:04 by root             ###   ########.fr       */
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

int loop_event(t_main *game)
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
