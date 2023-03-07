/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:58:57 by jmoutous          #+#    #+#             */
/*   Updated: 2022/11/22 11:46:53 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len_s;
	char	*cpy;

	len_s = ft_strlen(s1);
	cpy = malloc(sizeof(char) * (len_s + 1));
	if (cpy == NULL)
		return (NULL);
	ft_memcpy(cpy, s1, len_s);
	cpy[len_s] = '\0';
	return (cpy);
}
