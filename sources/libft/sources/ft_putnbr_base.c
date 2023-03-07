/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:44:37 by jmoutous          #+#    #+#             */
/*   Updated: 2023/02/17 10:40:11 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr(long long nbr, char *base, int ln_base)
{
	int	len;
	int	check_write;

	len = 0;
	if (nbr >= 0 && nbr < ln_base)
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

int	ft_putnbr_base(long long nbr, char *base)
{
	int	len;
	int	check_write;
	int	ln_base;

	len = 0;
	ln_base = 0;
	if (nbr < 0)
	{
		check_write = ft_putchar('-');
		if (check_write == -1)
			return (-1);
		len += check_write;
		nbr *= -1;
	}
	while (base[ln_base] != 0)
		ln_base++;
	check_write = ft_putnbr(nbr, base, ln_base);
	if (check_write == -1)
		return (-1);
	len += check_write;
	return (len);
}
