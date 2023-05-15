/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:47:49 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/15 16:12:05 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_conversion_fd(char c, va_list ap, int fd)
{
	if (c == 'c')
		return (ft_putchar_fd((char) va_arg(ap, int), fd));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(ap, char *), fd));
	else if (c == 'p')
		return (ft_dprint_address(va_arg(ap, unsigned long long), fd));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_base_fd(va_arg(ap, int), "0123456789", fd));
	else if (c == 'u')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int), "0123456789", fd));
	else if (c == 'x')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int),
				"0123456789abcdef", fd));
	else if (c == 'X')
		return (ft_putnbr_base_fd(va_arg(ap, unsigned int),
				"0123456789ABCDEF", fd));
	else if (c == '%')
		return (ft_putchar_fd('%', fd));
	else
		return (ft_putchar_fd(c, fd));
	return (0);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;
	int		check_write;

	va_start(ap, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			check_write = ft_conversion_fd(str[i], ap, fd);
		}
		else
			check_write = ft_putchar_fd(str[i], fd);
		i++;
		if (check_write == -1)
			return (-1);
		else
			len += check_write;
	}
	va_end(ap);
	return (len);
}
