/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:21:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/08 13:10:04 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_first_child(t_data *data, int **pipes, int i)
{
	(void) data;
	(void) pipes;
	(void) i;
	// if (dup2( , STDIN_FILENO) == -1 // add input
	// 	|| dup2(pipes[i][1], STDOUT_FILENO) == -1)
	// {
	// 	ft_close_fds(data);
	// 	perror("Error while duplicating file descriptor! ");
	// 	ft_quit(data);
	// 	exit (1);
	// }
}

static void	ft_last_child(t_data *data, int **pipes, int i)
{
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("Error while duplicating file descriptor! ");
		ft_quit(data);
		exit (1);
	}
}

static void	ft_middle_child(t_data *data, int **pipes, int i)
{
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1
		|| dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("Error while duplicating file descriptor! ");
		ft_quit(data);
		exit (1);
	}
}

void	ft_child(t_data *data, int **pipes, int i)
{
	if (i == 0)
		ft_first_child(data, pipes, i);
	else if (i == data->nb_cmd - 1)
		ft_last_child(data, pipes, i);
	else
		ft_middle_child(data, pipes, i);
	ft_close_fds(data);
	// execve(, data->cmd_args[i], data->envp);
	perror("\nError\nIn child process while executing command! ");
	ft_quit(data);
	exit(1);
}
