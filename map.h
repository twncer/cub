/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:32:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/09/03 05:34:21 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include "texture.h"
#include "utils.h"  // Added: for is_space and ft_strjoin declarations

typedef struct s_map t_map;
typedef struct s_main t_main;  // Forward declaration

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
	int			**matrix;
};

void	cub_map(char *map_location, t_main *game);
char	*cub_map_read(char *map_file);
void	parse_texture(char *raw_map, int id, int parsed[6], t_main *g);
void	parse_color(char *raw_map, int id, int parsed[6], t_main *g);
void	validate_map(char *raw_map);
int		**create_matrix(char *raw_map);  // Added: missing function declaration
// Note: create_matrix function is called but not defined - needs implementation

#endif
