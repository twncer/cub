/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusudemi <yusudemi@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 03:03:40 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/30 03:34:40 by yusudemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector		t_vector;
typedef struct s_vector_int	t_vector_int;
typedef struct s_segment	t_segment;
typedef struct s_angle		t_angle;

struct s_vector
{
	double	x;	
	double	y;	
};

struct s_vector_int
{
	int	x;
	int	y;
};

struct s_segment
{
	t_vector s;
	t_vector e;
};

struct s_angle
{
	double	s;
	double	e;
};

#endif