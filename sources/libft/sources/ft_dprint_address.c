/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprint_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:33:01 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/15 16:25:20 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbrfd(unsigned long long nbr,
	char *base, unsigned int ln_base, int fd)
{
	int	len;
	int	check_write;

	len = 0;
	if (nbr < ln_base)
	{
		check_write = ft_putchar_fd(base[nbr], fd);
		if (check_write == -1)
			return (-1);
		len += check_write;
	}
	if (nbr >= ln_base)
	{
		check_write = ft_putnbrfd(nbr / ln_base, base, ln_base, fd);
		if (check_write == -1)
			return (-1);
		len += check_write;
		check_write = ft_putnbrfd(nbr % ln_base, base, ln_base, fd);
		if (check_write == -1)
			return (-1);
		len += check_write;
	}
	return (len);
}

int	ft_dprint_address(unsigned long long arg, int fd)
{
	int	len;
	int	check_write;

	len = 0;
	check_write = ft_putstr_fd("0x", fd);
	if (check_write == -1)
		return (-1);
	len += check_write;
	check_write = ft_putnbrfd(arg, "0123456789abcdef", 16, fd);
	if (check_write == -1)
		return (-1);
	len += check_write;
	return (len);
}
