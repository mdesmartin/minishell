/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:50 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/30 12:58:58 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_builtin(t_data *data)
{
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "cd", 3) == 0)
	{
		if (s_read_cnt(data->cmd)->command[1] == NULL)
		{
			if (chdir(getenv("USER_ZDOTDIR")) == -1)
				perror("Error while calling chdir()! "); 
		}
		else if (s_read_cnt(data->cmd)->command[2] != NULL)
			ft_printf("cd: too many arguments\n");
		else if (chdir(s_read_cnt(data->cmd)->command[1]) == -1)
			perror("Error while calling chdir()! ");
		return (1);
	}
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "env", 4) == 0)
		return (ft_print_env(data), 1);
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "export", 7) == 0)
	{
		if (s_read_cnt(data->cmd)->command[1] == NULL)
			ft_print_export(data);
		else if (s_read_cnt(data->cmd)->command[2] != NULL)
			ft_printf("export: too many arguments\n");
		else if (ft_is_c_in(s_read_cnt(data->cmd)->command[1], '=') == 1)
			ft_export(data);
		return (1);
	}
	return (0);
}

static void	ft_process(t_data *data)
{
	int	i;
	int	pids;

	i = -1;
	data->nb_cmd = ft_lstsize(data->cmd);
	while (++i < data->nb_cmd - 1)
	{
		data->pipes[i] = malloc(2 * sizeof(int));
		if (!data->pipes[i])
			ft_error(data, "Malloc failed for data->pipes[i]");
		if (pipe(data->pipes[i]) == -1)
			ft_error(data, "Pipe failed for data->pipes[i]");
	}
	i = -1;
	while (++i < data->nb_cmd)
	{
		pids = fork();
		if (pids == -1)
			ft_error(data, "Fork failed");
		if (pids == 0)
			ft_child(data, data->pipes, i);
	}
	ft_close_fds(data);
	while (--i >= 0)
		wait(NULL);
}

void	ft_cmd(t_data *data)
{
	if (data->nb_cmd <= 1 && ft_builtin(data) != 0)
		return ;
	else
		ft_process(data);
}
