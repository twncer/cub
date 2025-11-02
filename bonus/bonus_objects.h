/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:13:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/31 12:58:24 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS
# define OBJECTS

typedef struct s_object_node	t_obj_node;
typedef struct s_object_list	t_obj_list;
typedef enum e_object_types		t_obj_type;
typedef struct s_fov_data		t_fov_data;

enum e_object_types
{
	DOOR,
	FIREBALL
};

struct s_object_node
{
	int		type;
	void	*object;
	t_obj_node	*next;
	// for render
	double		distance;
	t_obj_node	*next_render;
};

struct s_object_list
{
	t_obj_node *all;
	t_obj_node *to_render;
};


void	cub_objects(t_main *g);
void	add_object(t_obj_list *list, int type, void *obj);
void	add_to_render_queue(t_obj_list *list, t_obj_node *object, t_player *player);
void	clear_render_queue(t_obj_list *list);
void	create_render_queue(t_main *g);

#endif