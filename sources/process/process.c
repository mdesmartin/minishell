/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:36:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/17 13:37:13 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_exitcode;

static void	ft_pipe_init(t_data *data)
{
	int	i;

	i = -1;
	data->pipes = ft_calloc((data->nb_cmd + 1), sizeof(int *));
	if (!data->pipes)
		ft_perror(data, "Memory allocation failed: data->pipes", 12);
	while (++i < data->nb_cmd - 1)
	{
		data->pipes[i] = ft_calloc(2, sizeof(int));
		if (!data->pipes[i])
			ft_error(data, "Memory allocation failed for data->pipes[i]", 1);
		if (pipe(data->pipes[i]) == -1)
			ft_error(data, "Pipe failed for data->pipes[i]", 1);
	}
}

static void	ft_pipe_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_cmd - 1)
		free(data->pipes[i]);
	free(data->pipes);
	data->pipes = NULL;
}

static void	ft_wait_child(t_data *data, int i)
{
	int	status;

	g_exitcode += 2;
	while (--i >= 0)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			data->exit_code = WTERMSIG(status) + 128;
			if (data->exit_code == 131)
				printf("\b\bQuit\n");
			if (data->exit_code == 141)
				data->exit_code = 0;
		}
		else
			data->exit_code = 0;
	}
	g_exitcode -= 2;
}

static void	ft_process(t_data *data)
{
	int	i;
	int	pids;

	ft_pipe_init(data);
	i = -1;
	while (++i < data->nb_cmd)
	{
		pids = fork();
		if (pids == -1)
			ft_error(data, "Fork failed", 1);
		if (pids == 0)
			ft_child(data, data->pipes, i);
	}
	ft_close_fds(data, NULL);
	ft_wait_child(data, i);
	ft_pipe_free(data);
}

void	ft_cmd(t_data *data)
{
	char	**command;
	char	**input;
	char	**output;

	command = s_read_cnt(data->cmd)->command;
	input = (char **)s_read_cnt(data->cmd)->input;
	output = (char **)s_read_cnt(data->cmd)->output;
	data->nb_cmd = ft_lstsize(data->cmd);
	if (data->nb_cmd == 1 && !input[0] && !output[0]
		&& ft_builtin(data, command) != 0)
		return ;
	ft_process(data);
}
