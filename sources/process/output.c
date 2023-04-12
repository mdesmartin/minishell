/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:56:56 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/12 17:46:06 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// output[0] : 0 = > ; 1 = >>
// output[1] : file if output[0] == 0

void	ft_output_file(t_data *data)
{
	int	outfile;

	outfile = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// outfile = open((char *)s_read_cnt(data->cmd)->output[0],
	// 		O_WRONLY | O_APPEND | O_TRUNC, 0644);
	if (outfile == -1)
		ft_perror(data, "Error when creating or accessing outfile", 1);
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data, "Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
}

void	ft_output_appends(t_data *data)
{
	int	outfile;

	outfile = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	// outfile = open((char *)s_read_cnt(data->cmd)->output[0],
	// 		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		ft_perror(data, "Error when creating or accessing outfile", 1);
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data, "Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
}

void	ft_output_redirection(t_data *data)
{
	if (!(char *)s_read_cnt(data->cmd)->output[0])
		return ;
	else if ((char)s_read_cnt(data->cmd)->output[0][0] == '0')
		ft_output_file(data);
	else if ((char)s_read_cnt(data->cmd)->output[0][0] == '1')
		ft_output_appends(data);
}
