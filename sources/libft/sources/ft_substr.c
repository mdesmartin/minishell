/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:34:24 by jmoutous          #+#    #+#             */
/*   Updated: 2022/11/22 11:29:29 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_s;

	i = 0;
	if (ft_strlen(s) < start)
	{
		sub_s = malloc (sizeof (char));
		if (!sub_s)
			return (NULL);
		sub_s[0] = 0;
		return (sub_s);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub_s = malloc (sizeof (char) * (len + 1));
	if (!sub_s)
		return (NULL);
	while (i < len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
