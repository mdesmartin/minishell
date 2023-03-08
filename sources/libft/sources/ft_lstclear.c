/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:51:40 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/08 12:31:42 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void**))
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
