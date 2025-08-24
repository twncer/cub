/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 08:07:31 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 11:53:40 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_space(c)
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int get_map_height(char *raw_map)
{
	int	count;
	int	ret;

	count = 1;
	ret = 0;
	while (*raw_map)
	{
		if (*raw_map == '\n')
			count++;
		else if (!is_valid_map_char(*raw_map))
			cleanup("Map has invalid character");
		else
			ret = count;
		raw_map++;
	}
	return (ret);
}
// put 2 for spaces as placeholder. continue on rawmap including nl ((*rawmap)++) 
int	*create_map_line(char **raw_map)
{
	
}

int	**create_matrix(char *raw_map)
{
	int	**map;
	int	map_height;
	int	i;

	if (!*raw_map)
		cleanup("Missing map data");
	map_height = get_map_height(raw_map);
	map = malloc (sizeof(int *) * map_height);
	if (!map)
		cleanup("Memory allocation failed");
	i = -1;
	while (i++ < map_height)
	{
		map[i] = create_map_line(&raw_map);
		if (!map[i]) // needed
		{
			while (--i >= 0)
				free(map[i]);
			cleanup("Memory allocation failed");
		}
	}
	return (map);
}
