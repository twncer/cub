/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:32:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/08/24 11:20:49 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include "texture.h"

typedef struct s_map t_map;

enum e_identifiers
{
	NO = 0,
	SO,
	WE,
	EA,
	F,
	C,
	MAP
};

struct s_map
{
	t_texture	texture_no;
	t_texture	texture_so;
	t_texture	texture_we;
	t_texture	texture_ea;
	int			color_f;
	int			color_c;
	int			**map;
};

void	cub_map(char *map_location);
char	*cub_map_read(int fd);
void	cub_map_process(char *raw_map);
void	cub_map_parse(char *raw_map, int current_id);
void	validate_texture(char *raw_map, int id, int parsed[6]);
void	map_parse_texture(int id, char *relative_path, int ext);
int		find_id(char *raw_map);
int		is_space(char c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
