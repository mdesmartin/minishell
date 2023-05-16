/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:44:37 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/15 16:24:44 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbrfd(long long nbr, char *base, int ln_base, int fd)
{
	int	len;
	int	check_write;

	len = 0;
	if (nbr >= 0 && nbr < ln_base)
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

int	ft_putnbr_base_fd(long long nbr, char *base, int fd)
{
	int	len;
	int	check_write;
	int	ln_base;

	len = 0;
	ln_base = 0;
	if (nbr < 0)
	{
		check_write = ft_putchar_fd('-', fd);
		if (check_write == -1)
			return (-1);
		len += check_write;
		nbr *= -1;
	}
	while (base[ln_base] != 0)
		ln_base++;
	check_write = ft_putnbrfd(nbr, base, ln_base, fd);
	if (check_write == -1)
		return (-1);
	len += check_write;
	return (len);
}
