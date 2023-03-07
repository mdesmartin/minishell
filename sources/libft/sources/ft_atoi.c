/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:31:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/01/17 09:16:46 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_overflow(long int n, int last, int sign)
{
	if (n * sign != (n * 10 + last) / 10 * sign)
	{
		if ((n * 10 + last) / 10 * sign < 0)
			return (-1);
		else
			return (0);
	}
	return (42);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ft_check_overflow(res, str[i] - '0', sign) != 42)
			return (ft_check_overflow(res, str[i] - '0', sign));
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int) res * sign);
}
