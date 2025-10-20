/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 06:59:43 by yusudemi          #+#    #+#             */
/*   Updated: 2025/10/19 10:35:36 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"  // Added: for ft_strlen function declaration

#include "../gc/gc.h"
char	*ft_strjoin(char *str1, char *str2)
{
	char	*res;
	char	*ret;

	res = alloc_crit(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!res)
		return (NULL);
	ret = res;
	while (*str1)
		*res++ = *str1++;
	while (*str2)
		*res++ = *str2++;
	*res = '\0';
	return (ret);
}
// note that shi