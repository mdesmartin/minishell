/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:21:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/31 13:36:46 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_only_child(t_data *data)
{
	char	*path;

	ft_close_fds(data);
	path = ft_get_arg_path(data);
	// locenvp = ft_lst_to_tabtab(data->envp);
	execve(path, (char **)s_read_cnt(data->cmd)->command, NULL);
}

static void	ft_first_child(t_data *data, int **pipes, int i)
{
	char	*path;

	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("Error while duplicating file descriptor! ");
		ft_quit(data);
		exit (1);
	}
	if (ft_builtin(data) != 0)
	{
		ft_quit(data);
		exit(0);
	}
	path = ft_get_arg_path(data);
	execve(path, (char **)s_read_cnt(data->cmd)->command, NULL);
}

static void	ft_last_child(t_data *data, int **pipes, int i)
{
	char	*path;

	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("Error while duplicating file descriptor! ");
		ft_quit(data);
		exit (1);
	}
	ft_close_fds(data);
	while (i > 0)
	{
		data->cmd = data->cmd->next;
		i--;
	}
	if (ft_builtin(data) != 0)
	{
		ft_quit(data);
		exit(0);
	}
	path = ft_get_arg_path(data);
	execve(path, (char **)s_read_cnt(data->cmd)->command, NULL);
}

static void	ft_middle_child(t_data *data, int **pipes, int i)
{
	char	*path;

	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1
		|| dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("Error while duplicating file descriptor! ");
		ft_quit(data);
		exit (1);
	}
	ft_close_fds(data);
	while (i > 0)
	{
		data->cmd = data->cmd->next;
		i--;
	}
	if (ft_builtin(data) != 0)
	{
		ft_quit(data);
		exit(0);
	}
	path = ft_get_arg_path(data);
	execve(path, (char **)s_read_cnt(data->cmd)->command, NULL);
}

void	ft_child(t_data *data, int **pipes, int i)
{
	if (data->nb_cmd == 1)
		ft_only_child(data);
	else if (i == 0)
		ft_first_child(data, pipes, i);
	else if (i == data->nb_cmd - 1)
		ft_last_child(data, pipes, i);
	else
		ft_middle_child(data, pipes, i);
	perror("Error while executing command! ");
	ft_quit(data);
	exit(1);
}
