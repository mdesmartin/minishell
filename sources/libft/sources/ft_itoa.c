/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:31:32 by jmoutous          #+#    #+#             */
/*   Updated: 2022/11/22 08:41:05 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_count(int i)
{
	int	nb_count;

	nb_count = 0;
	while (i != 0)
	{
		nb_count++;
		i = i / 10;
	}
	return (nb_count);
}

static char	*ft_ito_neg(long int number)
{
	int			i;
	char		*res;

	number *= -1;
	i = ft_nb_count(number);
	res = ft_calloc((ft_nb_count(number) + 2), sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '-';
	while (number > 0)
	{
		res[i] = (number % 10) + 48;
		number = number / 10;
		i--;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	number;
	char		*res;

	if (n == 0)
		return (ft_strdup("0"));
	number = n;
	if (number < 0)
		return (ft_ito_neg(number));
	i = ft_nb_count(n) - 1;
	res = ft_calloc(i + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (number > 0)
	{
		res[i] = (number % 10) + 48;
		number = number / 10;
		i--;
	}
	return (res);
}
