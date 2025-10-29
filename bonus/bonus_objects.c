/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:22:07 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/29 09:25:28 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stddef.h>
void	add_object(t_obj_list *list, int type, void *obj);

static void	create_fireballs(t_main *g)
{
	int	i;
	t_fireball *fireball;

	i = -1;
	while (++i < NUM_OF_FIREBALLS)
	{
		fireball = malloc(sizeof(t_fireball)); // alloc_crit
		fireball->direction = 0.0;
		fireball->position.x = -1.0;
		fireball->position.y = -1.0;
		add_object(&g->objects, FIREBALL, fireball);
	}
}

static void	insert_barrier(t_door *door, t_vector_int map_pos, double axis)
{
	if (axis == 0) // horizontal
	{
		door->barrier_1.s.x = map_pos.x + 0.5 - (DOOR_THICKNESS / 2.0);
		door->barrier_1.s.y = map_pos.y + (1.0 - DOOR_WIDTH) / 2.0;
		door->barrier_1.e.x = map_pos.x + 0.5 - (DOOR_THICKNESS / 2.0);
		door->barrier_1.e.y = door->barrier_1.s.y + DOOR_WIDTH;
	
		door->barrier_2.s.x = map_pos.x + 0.5 + (DOOR_THICKNESS / 2.0);
		door->barrier_2.s.y = map_pos.y + (1.0 - DOOR_WIDTH) / 2.0;
		door->barrier_2.e.x = map_pos.x + 0.5 + (DOOR_THICKNESS / 2.0);
		door->barrier_2.e.y = door->barrier_1.s.y + (DOOR_WIDTH / 2.0);
	}
	else // vertical
	{
		door->barrier_1.s.x = map_pos.x + (1.0 - DOOR_WIDTH) / 2.0;
		door->barrier_1.s.y = map_pos.y + 0.5 - (DOOR_THICKNESS / 2.0);
		door->barrier_1.e.x = door->barrier_1.s.x + DOOR_WIDTH;
		door->barrier_1.e.y = map_pos.y + 0.5 - (DOOR_THICKNESS / 2.0);
	
		door->barrier_2.s.x = map_pos.x + (1.0 - DOOR_WIDTH) / 2.0;
		door->barrier_2.s.y = map_pos.y + 0.5 + (DOOR_THICKNESS / 2.0);
		door->barrier_2.e.x = door->barrier_2.s.x + DOOR_WIDTH;
		door->barrier_2.e.y = map_pos.y + 0.5 + (DOOR_THICKNESS / 2.0);
	}
	door->state = LOCKED;
}

static void	create_barriers(t_main *g)
{
	t_door_wall *door_wall;
	t_door		*door;
	int			i;

	door_wall = find_door_wall(-1, 0, NULL);
	i = 0;
	while (door_wall)
	{
		door = malloc(sizeof(t_door)); // alloc_crit
		insert_barrier(door, door_wall->map_pos, door_wall->axis);
		add_object(&g->objects, DOOR, door);
		door_wall = find_door_wall(-1, ++i, NULL);
	}
}
#include <stdio.h>

static void debug(t_main *g)
{
    t_obj_node *curr = g->objects.all;
    int fireball_count = 0;
    int door_count = 0;
    
    printf("=== OBJECT LIST DEBUG ===\n");
    
    while (curr)
    {
        if (curr->type == FIREBALL)
        {
            t_fireball *fb = (t_fireball *)curr->object;
            printf("FIREBALL #%d:\n", fireball_count++);
            printf("  Position: (%.2f, %.2f)\n", fb->position.x, fb->position.y);
            printf("  Direction: %.2f radians\n", fb->direction);
            printf("  Status: %s\n", (fb->position.x < 0) ? "INACTIVE" : "ACTIVE");
            printf("\n");
        }
        else if (curr->type == DOOR)
        {
            t_door *door = (t_door *)curr->object;
            printf("DOOR #%d:\n", door_count++);
            printf("  State: %d\n", door->state);
            printf("  Barrier 1:\n");
            printf("    Start: (%.2f, %.2f)\n", door->barrier_1.s.x, door->barrier_1.s.y);
            printf("    End:   (%.2f, %.2f)\n", door->barrier_1.e.x, door->barrier_1.e.y);
            printf("  Barrier 2:\n");
            printf("    Start: (%.2f, %.2f)\n", door->barrier_2.s.x, door->barrier_2.s.y);
            printf("    End:   (%.2f, %.2f)\n", door->barrier_2.e.x, door->barrier_2.e.y);
            printf("\n");
        }
        else
        {
            printf("UNKNOWN OBJECT TYPE: %d\n", curr->type);
        }
        curr = curr->next;
    }
    
    printf("=== SUMMARY ===\n");
    printf("Total Fireballs: %d\n", fireball_count);
    printf("Total Doors: %d\n", door_count);
    printf("Total Objects: %d\n", fireball_count + door_count);
    printf("==================\n\n");
}

void	cub_objects(t_main *g)
{
	create_fireballs(g);
	create_barriers(g);

	debug(g);
}