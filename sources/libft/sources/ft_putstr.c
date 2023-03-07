/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:39:41 by jmoutous          #+#    #+#             */
/*   Updated: 2023/02/17 10:40:11 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	i;
	int	len;
	int	check_write;

	i = 0;
	len = 0;
	if (s == NULL)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		check_write = ft_putchar(s[i]);
		if (check_write == -1)
			return (-1);
		len += check_write;
		i++;
	}
	return (len);
}
