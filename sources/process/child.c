/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:21:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/31 12:23:08 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_only_child(t_data *data)
{
	char	**command;
	char	*path;

	command = ft_redirection(data, 0);
	ft_close_fds(data, 0);
	ft_close_hd_fds(data);
	if (!command[0])
		ft_quit(data, data->exit_code);
	if (ft_builtin(data, command) != 0)
		ft_quit(data, data->exit_code);
	path = ft_get_arg_path(data, command);
	if (path)
	{
		execve(path, command, data->envp_tab);
		free(path);
	}
	if (ft_is_directory(command[0]) == 1)
		ft_builtin_slash(data, command[0]);
	return (command[0]);
}

static char	*ft_first_child(t_data *data, int **pipes, int i)
{
	char	**command;
	char	*path;

	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, 0);
		ft_error(data, "Error while duplicating file descriptor", 1);
	}
	command = ft_redirection(data, i);
	ft_close_fds(data, 0);
	ft_close_hd_fds(data);
	if (!command[0])
		ft_quit(data, data->exit_code);
	if (ft_builtin(data, command) != 0)
		ft_quit(data, data->exit_code);
	path = ft_get_arg_path(data, command);
	if (path)
	{
		execve(path, command, data->envp_tab);
		free(path);
	}
	if (ft_is_directory(command[0]) == 1)
		ft_builtin_slash(data, command[0]);
	return (command[0]);
}

static char	*ft_last_child(t_data *data, int **pipes, int i)
{
	char	**command;
	char	*path;

	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data, 0);
		ft_error(data, "Error while duplicating file descriptor", 1);
	}
	command = ft_redirection(data, i);
	ft_close_fds(data, 0);
	ft_close_hd_fds(data);
	if (!command[0])
		ft_quit(data, data->exit_code);
	if (ft_builtin(data, command) != 0)
		ft_quit(data, data->exit_code);
	path = ft_get_arg_path(data, command);
	if (path)
	{
		execve(path, command, data->envp_tab);
		free(path);
	}
	if (ft_is_directory(command[0]) == 1)
		ft_builtin_slash(data, command[0]);
	return (command[0]);
}

static char	*ft_middle_child(t_data *data, int **pipes, int i)
{
	char	**command;
	char	*path;

	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1
		|| dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, 0);
		ft_error(data, "Error while duplicating file descriptor", 1);
	}
	command = ft_redirection(data, i);
	ft_close_fds(data, 0);
	ft_close_hd_fds(data);
	if (!command[0])
		ft_quit(data, data->exit_code);
	if (ft_builtin(data, command) != 0)
		ft_quit(data, data->exit_code);
	path = ft_get_arg_path(data, command);
	if (path)
	{
		execve(path, command, data->envp_tab);
		free(path);
	}
	if (ft_is_directory(command[0]) == 1)
		ft_builtin_slash(data, command[0]);
	return (command[0]);
}

void	ft_child(t_data *data, int **pipes, int i)
{
	char	*command;

	if (data->nb_cmd == 1)
		command = ft_only_child(data);
	else if (i == 0)
		command = ft_first_child(data, pipes, i);
	else if (i == data->nb_cmd - 1)
		command = ft_last_child(data, pipes, i);
	else
		command = ft_middle_child(data, pipes, i);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		ft_error(data, "Error while duplicating file descriptor", 1);
	printf("minishell: %s: command not found\n", command);
	ft_quit(data, 127);
}
