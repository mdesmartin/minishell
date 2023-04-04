/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:56:56 by julien            #+#    #+#             */
/*   Updated: 2023/04/03 17:37:07 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// output[0] : 0 = > ; 1 = >>
// output[1] : file if output[0] == 0

void	ft_output_file(t_data *data)
{
	(void)data;
}

void	ft_output_appends(t_data *data)
{
	(void)data;
}

void	ft_output_redirection(t_data *data, int **pipes, int i)
{
	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data);
		perror("Error while duplicating file descriptor! ");
		ft_quit(data);
		exit (1);
	}
	if ((char)s_read_cnt(data->cmd)->output[0][0] == 0)
		ft_output_file(data);
	if ((char)s_read_cnt(data->cmd)->output[0][0] == 1)
		ft_output_appends(data);
}
