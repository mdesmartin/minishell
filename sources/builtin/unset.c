/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:12:06 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/24 12:12:36 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_onelst(t_envp **envp, char *variable)
{
	t_envp	*current;
	t_envp	*previous;

	current = *envp;
	previous = *envp;
	while (current)
	{
		if (ft_strncmp(current->variable, variable, ft_strlen(variable)) == 0
			&& ft_strlen(current->variable) == ft_strlen(variable))
		{
			if (current == *envp)
				*envp = (*envp)->next;
			else
				previous->next = current->next;
			free(current->variable);
			free(current->value);
			free(current);
			return ;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

static int	ft_check_unsetvar(char *variable)
{
	int	i;

	i = 1;
	if (ft_isalpha(variable[0]) == 0 && variable[0] != '_')
	{
		ft_dprintf(2, "minishell : unset: `%s': not a valid identifier\n",
			variable);
		return (1);
	}
	while (variable[i])
	{
		if (ft_isalnum(variable[i]) == 0 && variable[i] != '_')
		{
			ft_dprintf(2, "minishell : unset: `%s': not a valid identifier\n",
				variable);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_unset(t_data *data, char **command)
{
	int	i;

	i = 1;
	data->exit_code = 0;
	if (ft_strncmp("-", command[1], 1) == 0)
	{
		ft_dprintf(2, "minishell : unset: %c%c : invalid option\n",
			command[1][0], command[1][1]);
		data->exit_code = 2;
		return ;
	}
	while (command[i])
	{
		if (ft_check_unsetvar(command[i]) == 1)
			data->exit_code = 1;
		else if (ft_strncmp("_", command[i], 2) != 0)
			ft_del_onelst(&data->envp, command[i]);
		i++;
	}
	ft_update_envptab(data);
}
