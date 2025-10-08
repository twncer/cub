/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 03:32:21 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/08 03:07:29 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include "texture.h"
#include "utils.h"
#include "player.h"

typedef struct s_map	t_map;
typedef struct s_main	t_main;

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
	char		**matrix;
	t_player	player;
};

void	cub_map(char *map_location, t_main *game);
char	*cub_map_read(char *map_file);
void	parse_texture(char *raw_map, int id, int parsed[6], t_main *game);
void	parse_color(char *raw_map, int id, int parsed[6], t_main *game);
void	validate_map(char *raw_map);
void	parse_matrix(char *raw_map, t_main *game);  // Added: function to validate the map matrix
int		create_matrix(char *raw_map, t_main *game);  // Added: missing function declaration
// Note: create_matrix function is called but not defined - needs implementation
void	map_cleanup_exit(char *errmsg, t_main *game);
void	map_cleanup(t_main *game);

#endif
