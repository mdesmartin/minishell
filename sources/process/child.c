/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:21:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/06 16:17:01 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_only_child(t_data *data)
{
	char	*path;

ft_print_tabtab((char **)s_read_cnt(data->cmd)->command);
	ft_input_redirection(data);
	// ft_output_redirection(data);
	ft_close_fds(data);
	path = ft_get_arg_path(data);
	execve(path, (char **)s_read_cnt(data->cmd)->command, data->envp_tab);
}

static void	ft_first_child(t_data *data, int **pipes, int i)
{
	char	*path;

	// ft_input_redirection(data);
	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("First child : Error while duplicating file descriptor! ");
		ft_quit(data, 1);
	}
	ft_close_fds(data);
	if (ft_builtin(data) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data);
	execve(path, (char **)s_read_cnt(data->cmd)->command, data->envp_tab);
}

static void	ft_last_child(t_data *data, int **pipes, int i)
{
	char	*path;

	// ft_output_redirection(data);
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("Last child : Error while duplicating file descriptor! ");
		ft_quit(data, 1);
	}
	ft_close_fds(data);
	while (i > 0)
	{
		data->cmd = data->cmd->next;
		i--;
	}
	if (ft_builtin(data) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data);
	execve(path, (char **)s_read_cnt(data->cmd)->command, data->envp_tab);
}

static void	ft_middle_child(t_data *data, int **pipes, int i)
{
	char	*path;

	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1
		|| dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("Error while duplicating file descriptor! ");
		ft_quit(data, 1);
	}
	ft_close_fds(data);
	while (i > 0)
	{
		data->cmd = data->cmd->next;
		i--;
	}
	if (ft_builtin(data) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data);
	execve(path, (char **)s_read_cnt(data->cmd)->command, data->envp_tab);
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
	ft_putstr3_fd((char *)s_read_cnt(data->cmd)->command[0],
		": command", " not found\n");
	ft_quit(data, 1);
}
