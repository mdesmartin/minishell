/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:55:55 by jmoutous          #+#    #+#             */
/*   Updated: 2022/11/22 08:43:37 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (!*s1 || !*set)
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i++;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[j]) != 0 && j != i)
		j--;
	return (ft_substr(s1, i, (j - i + 1)));
}
