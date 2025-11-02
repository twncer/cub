/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 07:15:39 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/31 03:07:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// Utility functions for string and character operations
int		is_space(char c);                    // Fixed: was ft_isspace
int		ft_strlen(const char *s);            // String length function
char	*ft_strjoin(char *str1, char *str2);  // Fixed: was strjoin
int	ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);

#endif