/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:12:06 by julien            #+#    #+#             */
/*   Updated: 2023/03/31 13:48:04 by mehdidesmar      ###   ########lyon.fr   */
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
			free(current);
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
	while (s_read_cnt(data->cmd)->command[i])
	{
		if (ft_strncmp("_", s_read_cnt(data->cmd)->command[i], 2) != 0)
			ft_del_onelst(data->envp, (char *) s_read_cnt(data->cmd)->command[i]);
		i++;
	}
	ft_free_envptab(data);
	data->envp_tab = ft_lst_to_tabtab(data->envp);
}
