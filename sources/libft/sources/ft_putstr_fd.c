/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:33:35 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/15 15:51:25 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	len;
	int	check_write;

	i = 0;
	len = 0;
	if (s == NULL)
		return (ft_putstr_fd("(null)", fd));
	while (s[i])
	{
		check_write = ft_putchar_fd(s[i], fd);
		if (check_write == -1)
			return (-1);
		len += check_write;
		i++;
	}
	return (len);
}
