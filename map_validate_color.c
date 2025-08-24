/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 07:07:17 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 08:38:10 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	validate_format(char *color, int len)
{
	int	i;
	int	commas;
	int	comma_seen;
	
	i = -1;
	commas = 0;
	comma_seen = 1;
	while (i++ < len)
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
		cleanup("Invalid character in color value");
	}
	if (comma_seen = 1 || commas != 2)
		cleanup("Missing RGB component in color value");
}

static int	extract_rgb_component(char **str)
{
	int	value;
	
	value = 0;
	while (**str >= '0' && **str <= 9)
	{
		value = value * 10 + (**str - '0');
		if (value > 255)
			cleanup("RGB component must be between 0-255");
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
		cleanup("Missing RGB component in color value");
	validate_format(color_start, color_len);
	return (str_to_rgb(color_start));
}

void	validate_color(char *raw_map, int id, int parsed[6])
{
	int	rgb;
	
	if (parsed[id])
		cleanup("Duplicate color identifier");
	// get color, validate in raw, then transform it to int end return
	rgb = extract_color(raw_map);
	map_parse_color(rgb);
	parsed[id] = 1;
}