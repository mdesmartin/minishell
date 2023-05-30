/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:52:20 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/30 14:11:23 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_builtin_export(t_data *data, char **command)
{
	data->exit_code = 0;
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

static void	ft_builtin_pwd(t_data *data, char **command)
{
	data->exit_code = 0;
	if (command[1] && command[1][0] == '-')
	{
		if ((command[1][1] && command[1][1] != '-')
			|| (command[1][1] == '-' && command[1][2]))
		{
			ft_dprintf(2, "minishell : pwd: %c%c : invalid option\n",
				command[1][0], command[1][1]);
			data->exit_code = 2;
			return ;
		}
	}
	printf("%s\n", data->pwd);
}

int	ft_builtin(t_data *data, char **command)
{
	if (ft_strncmp(command[0], "cd", 3) == 0)
		return (ft_builtin_cd(data, command), 1);
	if (ft_strncmp(command[0], "exit", 5) == 0)
		return (ft_builtin_exit(data, command), 1);
	if (ft_strncmp(command[0], "echo", 5) == 0)
		return (ft_builtin_echo(data, command), 1);
	if (ft_strncmp(command[0], "env", 4) == 0)
		return (ft_check_envarg(data, command), 1);
	if (ft_strncmp(command[0], "pwd", 4) == 0)
		return (ft_builtin_pwd(data, command), 1);
	if (ft_strncmp(command[0], "export", 7) == 0)
		return (ft_builtin_export(data, command), 1);
	if (ft_strncmp(command[0], "unset", 6) == 0)
		return (ft_builtin_unset(data, command), 1);
	return (0);
}
