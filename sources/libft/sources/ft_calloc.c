/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:46:29 by jmoutous          #+#    #+#             */
/*   Updated: 2023/01/03 13:07:20 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*memspc;

	if (size > 0 && count > (SIZE_MAX / size))
		return (NULL);
	memspc = malloc(count * size);
	if (!memspc)
		return (NULL);
	ft_bzero(memspc, count * size);
	return (memspc);
}
