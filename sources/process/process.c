/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:36:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/31 12:23:42 by jmoutous         ###   ########lyon.fr   */
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
		ft_error(data, "Memory allocation failed: data->pipes", 12);
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

static void	ft_wait_child(t_data *data, int pid, int i)
{
	int	status;

	g_exitcode += 2;
	waitpid(pid, &status, 0);
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
	while (--i >= 1)
		wait(NULL);
	g_exitcode -= 2;
}

static void	ft_process(t_data *data)
{
	int	i;
	int	pids;
	int	stop;

	ft_pipe_init(data);
	stop = ft_process_here_doc(data);
	if (stop == 0)
	{
		i = -1;
		while (++i < data->nb_cmd)
		{
			pids = fork();
			if (pids == -1)
				ft_error(data, "Fork failed", 1);
			if (pids == 0)
				ft_child(data, data->pipes, i);
		}
		ft_close_hd_fds(data);
	}
	ft_close_fds(data, 0);
	if (stop == 0)
		ft_wait_child(data, pids, i);
	ft_pipe_free(data);
}

void	ft_cmd(t_data *data)
{
	char	**command;
	char	**redirections;

	command = s_read_cnt(data->cmd)->command;
	redirections = s_read_cnt(data->cmd)->redirections;
	data->nb_cmd = ft_lstsize(data->cmd);
	if (command[0] && data->nb_cmd == 1 && redirections[0]
		&& ft_strncmp(command[0], "exit", 5) == 0)
		ft_exit_redir(data, command, redirections);
	else if (data->nb_cmd == 1 && !redirections[0]
		&& ft_builtin(data, command) != 0)
		return ;
	else
		ft_process(data);
}
