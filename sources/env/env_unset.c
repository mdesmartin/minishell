/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:12:06 by julien            #+#    #+#             */
/*   Updated: 2023/03/27 16:49:25 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_onelst(t_envp *envp, char *variable)
{
	t_envp	*current;
	t_envp	*previous;

	current = envp;
	previous = envp;
	while (current)
	{
		if (ft_strncmp(current->variable, variable, ft_strlen(variable)) == 0
			&& ft_strlen(current->variable) == ft_strlen(variable))
		{
			previous->next = current->next;
			free(current->variable);
			free(current->value);
			break ;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

void	ft_unset(t_data *data)
{
	int	i;

	i = 1;
	while (data->cmd->content[i])
	{
		ft_del_onelst(data->envp, (char *) data->cmd->content[i]);
		i++;
	}
}
