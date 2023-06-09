/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:33:39 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/01 13:33:42 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envp	*ft_envlast(t_envp *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_envadd_back(t_envp **lst, t_envp *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_envlast(*lst)->next = new;
	return ;
}

void	ft_free_envplst(t_data *data)
{
	t_envp	*current;
	t_envp	*previous;

	if (!data->envp)
		return ;
	current = data->envp;
	while (current)
	{
		free(current->value);
		free(current->variable);
		current->value = NULL;
		current->variable = NULL;
		previous = current;
		current = current->next;
		free(previous);
		previous = NULL;
	}
	data->envp = NULL;
}
