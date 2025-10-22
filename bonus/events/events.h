/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:37:23 by btuncer           #+#    #+#             */
/*   Updated: 2025/10/22 20:47:38 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "../main/main.h"
# include <unistd.h>
# include <stdlib.h>

int onpress_event(int key, t_main *game);
int onrelease_event(int key, t_main *game);
int loop_event(t_main *game);
int terminate_hook(void);
void unlock_switch(t_main *game);

#endif