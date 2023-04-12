/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:21:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/12 17:46:06 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_only_child(t_data *data)
{
	char	*path;

	ft_input_redirection(data);
	// ft_output_redirection(data);
	ft_close_fds(data, NULL);
	path = ft_get_arg_path(data, (char **)s_read_cnt(data->cmd)->command);
	execve(path, (char **)s_read_cnt(data->cmd)->command, data->envp_tab);
}

static void	ft_first_child(t_data *data, int **pipes, int i)
{
	char	*path;

	ft_input_redirection(data);
	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data, "First child: Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
	ft_close_fds(data, NULL);
	if (ft_builtin(data, (char **)s_read_cnt(data->cmd)->command) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data, (char **)s_read_cnt(data->cmd)->command);
	execve(path, (char **)s_read_cnt(data->cmd)->command, data->envp_tab);
	ft_putstr3_fd((char *)s_read_cnt(data->cmd)->command[0],
		": command", " not found\n");
	ft_quit(data, 1);
}

static void	ft_last_child(t_data *data, int **pipes, int i)
{
	char	*path;
	t_list	*tmp;

	tmp = data->cmd;
	// ft_output_redirection(data);
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data, "Last child: Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
	ft_close_fds(data, NULL);
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	if (ft_builtin(data, (char **)s_read_cnt(tmp)->command) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data, (char **)s_read_cnt(tmp)->command);
	execve(path, (char **)s_read_cnt(tmp)->command, data->envp_tab);
	ft_putstr3_fd((char *)s_read_cnt(tmp)->command[0],
		": command", " not found\n");
	ft_quit(data, 1);
}

static void	ft_middle_child(t_data *data, int **pipes, int i)
{
	char	*path;
	t_list	*tmp;

	tmp = data->cmd;
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1
		|| dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data, "Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
	ft_close_fds(data, NULL);
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	if (ft_builtin(data, (char **)s_read_cnt(tmp)->command) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data, (char **)s_read_cnt(tmp)->command);
	execve(path, (char **)s_read_cnt(tmp)->command, data->envp_tab);
	ft_putstr3_fd((char *)s_read_cnt(tmp)->command[0],
		": command", " not found\n");
	ft_quit(data, 1);
}

void	ft_child(t_data *data, int **pipes, int i)
{
	get_rediction(data, i);
	if (data->nb_cmd == 1)
		ft_only_child(data);
	else if (i == 0)
		ft_first_child(data, pipes, i);
	else if (i == data->nb_cmd - 1)
		ft_last_child(data, pipes, i);
	else
		ft_middle_child(data, pipes, i);
}
