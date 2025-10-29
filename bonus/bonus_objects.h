/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 02:13:10 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/29 06:51:12 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS
# define OBJECTS

typedef struct s_object_node	t_obj_node;
typedef struct s_object_list	t_obj_list;
typedef enum e_object_types		t_obj_type;

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
void	add_to_render_queue(t_obj_list *list, t_obj_node *node, double distance);
void	clear_render_queue(t_obj_list *list);

#endif