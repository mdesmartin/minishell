/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:56:13 by jmoutous          #+#    #+#             */
/*   Updated: 2023/02/17 10:40:11 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_g(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	ft_strcpy_g(char *cpy, char *src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (i);
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin_g(char *dst, char *src)
{
	char	*res;
	int		i;
	int		j;

	if (!src)
		return (dst);
	i = 0;
	j = 0;
	res = ft_calloc((ft_strlen_g(dst) + ft_strlen_g(src) + 1), sizeof(char));
	if (!res)
	{
		if (dst)
			free (dst);
		return (NULL);
	}
	i = ft_strcpy_g(res, dst);
	while (src[j])
	{
		res[i + j] = src[j];
		j++;
	}
	res[i + j] = '\0';
	if (dst)
		free(dst);
	return (res);
}
