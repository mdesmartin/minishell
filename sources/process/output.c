/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:56:56 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/13 13:09:13 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// output[0] : 0 = > ; 1 = >>
// output[1] : file if output[0] == 0

static void	ft_output_file(t_data *data, char *file, int last_redir)
{
	int	outfile;

	outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		ft_perror(data, "Error when creating or accessing outfile", 1);
	if (last_redir == 1)
	{
		close(outfile);
		return ;
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data, "Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
}

static void	ft_output_appends(t_data *data, char *file, int last_redir)
{
	int	outfile;

	outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		ft_perror(data, "Error when creating or accessing outfile", 1);
	if (last_redir == 1)
	{
		close(outfile);
		return ;
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data, "Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
}

void	ft_output_redirection(t_data *data, char **output)
{
	int		last_redir;
	int		i;

	i = 0;
	while (output[i] && output[i + 1])
	{
		if (!output[i + 2])
			last_redir = 0;
		else
			last_redir = 1;
		if (output[0][0] == '0')
			ft_output_file(data, output[i + 1], last_redir);
		else if (output[0][0] == '1')
			ft_output_appends(data, output[i + 1], last_redir);
		i += 2;
	}
}
