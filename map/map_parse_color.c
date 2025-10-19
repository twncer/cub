/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 07:07:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 10:30:46 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main/main.h"
#include <stdio.h>   // Added: for printf function
#include <stdlib.h>  // Added: for exit function

static void	validate_format(char *color, int len)
{
	int	i;
	int	commas;
	int	comma_seen;
	
	i = -1;
	commas = 0;
	comma_seen = 1;
	while (++i < len)
	{
		if (color[i] == ',' && comma_seen == 0)
		{
			comma_seen = 1;
			commas++;
		}
		else if (color[i] >= '0' && color[i] <= '9')
		{
			comma_seen = 0;
			continue ;
		}
	}
	if (comma_seen == 1 || commas != 2)
	{
		printf("Error: not valid color value\n"); // find error msg for here
		exit(1);
	}
}

static int	extract_rgb_component(char **str)
{
	int	value;
	
	value = 0;
	// Fixed: character comparison should be with '9' not 9
	while (**str >= '0' && **str <= '9')
	{
		value = value * 10 + (**str - '0');
		if (value > 255)
		{
			printf("Error: RGB component must be between 0-255\n");
			exit(1);
		}
		(*str)++;  // Added: missing pointer increment
	}
	return (value);
}

static int	str_to_rgb(char	*color)
{
	int rgb[3];
	int	i;
	
	i = 0;
	while (i < 3)
	{
		rgb[i] = extract_rgb_component(&color);
		if (i < 2) // Skip comma after first two components
		{
			if (*color == ',')
				color++;
			else
			{
				printf("Error: Invalid character in color value\n");
				exit(1);
			}
		}
		i++;
	}
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
static int	extract_color(char *color_start)
{
	char	*color_end;
	int		color_len;

	color_start++;
	while (*color_start && is_space(*color_start))
		color_start++;
	color_end = color_start;
	while (*color_end && !is_space(*color_end) && *color_end != '\n')
		color_end++;
	color_len = color_end - color_start;
	if (color_len < 5)
	{
		printf("Error: Missing RGB component in color value\n");
		exit(1);
	}
	validate_format(color_start, color_len);
	return (str_to_rgb(color_start));
}

void	parse_color(char *raw_map, int id, int parsed[6], t_main *g)
{
	int	rgb;

	if (parsed[id])
	{
		printf("Error: Duplicate color identifier\n");
		exit(1);
	}
	
	// get color, validate in raw, then transform it to int end return
	rgb = extract_color(raw_map);
	
	if (id == C)
		g->map.color_c = rgb;
	else if (id == F)
		g->map.color_f = rgb;
	parsed[id] = 1;
}