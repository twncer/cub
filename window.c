/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 04:31:29 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/04 05:20:23 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "minilibx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>

#include <stdio.h>
/*
◦ The left and right arrow keys of the keyboard must allow you to look left and
	right in the maze.
◦ The W, A, S, and D keys must allow you to move the point of view through
	the maze.
◦ Pressing ESC must close the window and quit the program cleanly.
◦ Clicking on the red cross on the window’s frame must close the window and
	quit the program cleanly.
*/

static int	quit(t_main *g) // if u implement destructor this func can take void!
{
	mlx_destroy_image(g->window.mlx, g->window.img);
	mlx_destroy_window(g->window.mlx, g->window.win);
	map_cleanup(g); // needs mlx connection for cleanup
	exit(0);
	return(0);
}

void change_pos() // delete later test func
{
	return;
}
void change_dov() // delete later test func
{
	return;
}
void render() // delete later test func
{
	return;
}

static int	keys(int key, t_main *g)
{
	printf("here\n");
	if (key == XK_Escape) // escape key to quit
		quit(g);
	if (key == XK_w)
		change_pos(); // add this to player.c maybe. 
		// (not just player.x++ or smthng it should be changed according to direction)
	if (key == XK_s)
		change_pos(); // 
	if (key == XK_a)
		change_pos(); //
	if (key == XK_d)
		change_pos(); //
	if (key == XK_Right) // 
		change_dov(); // just change the it a lil bit like 
		// (player.dov + M_PI * 0.2) % M_PI * 2 === dov + 36degrees(this might be too much but try) % 360degrees
	if (key == XK_Left)
		change_dov(); // just change the it a lil bit like dov - M_PI * 0.2
	render(); // jmp to render game
	return(0);
}

void	cub_create_window(t_main *g)
{
	t_window *d;

	d = &g->window;
	d->win = mlx_new_window(d->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!d->win)
	{
		mlx_destroy_display(d->win);
		free(d->mlx);
		exit(1);
	}
	d->img = mlx_new_image(d->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!d->img)
	{
		mlx_destroy_window(d->mlx, d->win);
		mlx_destroy_display(d->win);
		free(d->mlx);
		exit(1);
	}
	d->addr = mlx_get_data_addr(d->img, &(d->bits_per_pixel),
			&(d->line_length), &(d->endian));
	printf("here\n");
	mlx_hook(d->win, ClientMessage, StructureNotifyMask, quit, g); // red cross stuff
	mlx_hook(d->win, KeyPress, KeyPressMask, keys, g); // keys
}
