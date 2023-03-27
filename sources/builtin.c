/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:52:20 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/27 16:11:47 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_builtin_cd(t_data *data)
{
	if (data->cmd->content[1] == NULL)
	{
		if (chdir(getenv("USER_ZDOTDIR")) == -1)
			perror("Error while calling chdir()! ");
	}
	else if (data->cmd->content[2] != NULL)
		ft_printf("cd: too many arguments\n");
	else if (chdir(data->cmd->content[1]) == -1)
		perror("Error while calling chdir()! ");
}

static void	ft_builtin_export(t_data *data)
{
	if (data->cmd->content[1] == NULL)
		ft_print_export(data);
	else if (data->cmd->content[2] != NULL)
		ft_printf("export: too many arguments\n");
	else if (ft_is_c_in(data->cmd->content[1], '=') == 1)
		ft_export(data);
}

static void	ft_builtin_unset(t_data *data)
{
	if (data->cmd->content[1] == NULL)
		return ;
	else
		ft_unset(data);
}

int	ft_builtin(t_data *data)
{
	if (ft_strncmp(data->cmd->content[0], "cd", 3) == 0)
		return (ft_builtin_cd(data), 1);
	if (ft_strncmp(data->cmd->content[0], "exit", 5) == 0)
		return (ft_quit(data), exit(0), 1);
	if (ft_strncmp(data->cmd->content[0], "env", 4) == 0)
		return (ft_print_env(data), 1);
	if (ft_strncmp(data->cmd->content[0], "export", 7) == 0)
		return (ft_builtin_export(data), 1);
	if (ft_strncmp(data->cmd->content[0], "unset", 6) == 0)
		return (ft_builtin_unset(data), 1);
	return (0);
}
