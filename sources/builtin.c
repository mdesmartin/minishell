/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:52:20 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/29 15:23:57 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_builtin_export(t_data *data)
{
	if (data->cmd->content[1] == NULL)
		ft_print_export(data);
	else
		ft_export(data);
}

static void	ft_builtin_unset(t_data *data)
{
	if (data->cmd->content[1] == NULL)
		return ;
	else
		ft_unset(data);
}

static void	ft_builtin_pwd(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->variable, 4) == 0)
			break ;
		tmp = tmp->next;
	}
	ft_printf("%s\n", tmp->value);
}

int	ft_builtin(t_data *data)
{
	if (ft_strncmp(data->cmd->content[0], "cd", 3) == 0)
		return (ft_builtin_cd(data), 1);
	if (ft_strncmp(data->cmd->content[0], "exit", 5) == 0)
		return (ft_quit(data), exit(0), 1);
	if (ft_strncmp(data->cmd->content[0], "env", 4) == 0)
		return (ft_print_env(data), 1);
	if (ft_strncmp(data->cmd->content[0], "pwd", 4) == 0)
		return (ft_builtin_pwd(data), 1);
	if (ft_strncmp(data->cmd->content[0], "export", 7) == 0)
		return (ft_builtin_export(data), 1);
	if (ft_strncmp(data->cmd->content[0], "unset", 6) == 0)
		return (ft_builtin_unset(data), 1);
	return (0);
}
