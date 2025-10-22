/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:29:09 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/22 20:47:41 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include <X11/keysym.h>

#include <stdio.h> // for debug

// 	switch keys are for player to be not able to spam some events by just
// continuously pressing on the key. switch key attribute provide a safe
// switching between active and inactive
static void onpress_switch_key(t_switch_key *switch_key)
{
	switch_key->key = true;
	if (!switch_key->key_switch)
	{
		printf("im doing a press event!\n"); // event that will happen when pressed
		switch_key->key_switch = true;
	}
}

static void onrelease_switch_key(t_switch_key *switch_key)
{
	switch_key->key = false;
}

void unlock_switch(t_main *game)
{
	if (game->key_list.e.key == false)
		game->key_list.e.key_switch = false;
	if (game->key_list.q.key == false)
		game->key_list.q.key_switch = false;
	if (game->key_list.spc.key == false)
		game->key_list.spc.key_switch = false;
}

int onpress_event(int key, t_main *game)
{
	if (key == XK_w)
		game->key_list.w = true;
	else if (key == XK_a)
		game->key_list.a = true;
	else if (key == XK_s)
		game->key_list.s = true;
	else if (key == XK_d)
		game->key_list.d = true;
	else if (key == XK_Left)
		game->key_list.arrow_l = true;
	else if (key == XK_Right)
		game->key_list.arrow_r = true;
	else if (key == XK_e)
		onpress_switch_key(&(game->key_list.e));
	else if (key == XK_q)
		onpress_switch_key(&(game->key_list.q));
	else if (key == XK_space)
		onpress_switch_key(&(game->key_list.spc));
	return (0);
}

int onrelease_event(int key, t_main *game)
{
	if (key == XK_Escape)
		terminate_hook();

	if (key == XK_w)
		game->key_list.w = false;
	else if (key == XK_a)
		game->key_list.a = false;
	else if (key == XK_s)
		game->key_list.s = false;
	else if (key == XK_d)
		game->key_list.d = false;
	else if (key == XK_Left)
		game->key_list.arrow_l = false;
	else if (key == XK_Right)
		game->key_list.arrow_r = false;
	else if (key == XK_e)
		onrelease_switch_key(&(game->key_list.e));
	else if (key == XK_q)
		onrelease_switch_key(&(game->key_list.q));
	else if (key == XK_space)
		onrelease_switch_key(&(game->key_list.spc));
	return (0);
}
