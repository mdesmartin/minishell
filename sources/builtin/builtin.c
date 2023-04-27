/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:52:20 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/27 15:18:18 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_builtin_export(t_data *data, char **command)
{
	if (command[1] == NULL)
		ft_print_export(data);
	else
		ft_export(data, command);
}

static void	ft_builtin_unset(t_data *data, char **command)
{
	if (command[1] == NULL)
		return ;
	else
		ft_unset(data, command);
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
	if (tmp->value)
		printf("%s", tmp->value);
	printf("\n");
}

int	ft_builtin(t_data *data, char **command)
{
	if (ft_strncmp(command[0], "cd", 3) == 0)
		return (ft_builtin_cd(data, command), 1);
	if (ft_strncmp(command[0], "exit", 5) == 0)
		return (ft_builtin_exit(data, command), 1);
	if (ft_strncmp(command[0], "echo", 5) == 0)
		return (ft_builtin_echo(command), 1);
	if (ft_strncmp(command[0], "env", 4) == 0)
		return (ft_check_envarg(data, command), 1);
	if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (ft_builtin_pwd(data), 1);
	if (ft_strncmp(command[0], "export", 7) == 0)
		return (ft_builtin_export(data, command), 1);
	if (ft_strncmp(command[0], "unset", 6) == 0)
		return (ft_builtin_unset(data, command), 1);
	return (0);
}
