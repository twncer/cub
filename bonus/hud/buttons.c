/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 00:55:21 by root              #+#    #+#             */
/*   Updated: 2025/11/03 06:16:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud.h"

void *set_button(t_button *button, bool hover, t_im *img, t_vector pos)
{
    int width;
    int height;

    button->hover = hover; // null check falan filan
    button->image = *img;
    button->position = pos;
    width = img->width;
    height = img->height;
    if (hover)
        width = width / 2;
    button->width = width;
    button->height = height;
    return (button);
}
