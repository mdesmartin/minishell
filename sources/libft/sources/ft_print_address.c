/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:33:01 by jmoutous          #+#    #+#             */
/*   Updated: 2023/02/17 10:40:11 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr(unsigned long long nbr, char *base, unsigned int ln_base)
{
	int	len;
	int	check_write;

	len = 0;
	if (nbr < ln_base)
	{
		check_write = ft_putchar(base[nbr]);
		if (check_write == -1)
			return (-1);
		len += check_write;
	}
	if (nbr >= ln_base)
	{
		check_write = ft_putnbr(nbr / ln_base, base, ln_base);
		if (check_write == -1)
			return (-1);
		len += check_write;
		check_write = ft_putnbr(nbr % ln_base, base, ln_base);
		if (check_write == -1)
			return (-1);
		len += check_write;
	}
	return (len);
}

int	ft_print_address(unsigned long long arg)
{
	int	len;
	int	check_write;

	len = 0;
	check_write = ft_putstr("0x");
	if (check_write == -1)
		return (-1);
	len += check_write;
	check_write = ft_putnbr(arg, "0123456789abcdef", 16);
	if (check_write == -1)
		return (-1);
	len += check_write;
	return (len);
}
