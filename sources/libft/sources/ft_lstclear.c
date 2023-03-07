/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:51:40 by mvogel            #+#    #+#             */
/*   Updated: 2023/02/14 15:45:56 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*nxt;

	if (!del || !lst || !*lst)
		return ;
	if (lst)
	{
		current = *lst;
		while (current)
		{
			nxt = current->next;
			ft_lstdelone(current, (del));
			current = nxt;
		}
		*lst = NULL;
	}
}
