/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:11:51 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/01 13:30:27 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_output_file(t_data *data, char *file)
{
	char	*msg;
	int		outfile;

	outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		msg = ft_strjoin("minishell: ", file);
		if (!msg)
			ft_error(data, "Error when creating error message", 12);
		perror(msg);
		free(msg);
		ft_quit(data, 1);
	}
	ft_close(outfile);
}

static void	ft_output_appends(t_data *data, char *file)
{
	char	*msg;
	int		outfile;

	outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
	{
		msg = ft_strjoin("minishell: ", file);
		if (!msg)
			ft_error(data, "Error when creating error message", 12);
		perror(msg);
		free(msg);
		ft_quit(data, 1);
	}
	ft_close(outfile);
}

void	ft_exit_redir(t_data *data, char **command, char **redirections)
{
	int	stop;
	int	i;

	i = 0;
	stop = ft_process_here_doc(data);
	ft_close_hd_fds(data);
	while (redirections[i] && redirections[i + 1])
	{
		if (redirections[i][0] == '0' || redirections[i][0] == '1')
			;
		else if (redirections[i][0] == '2')
			ft_output_file(data, redirections[i + 1]);
		else if (redirections[i][0] == '3')
			ft_output_appends(data, redirections[i + 1]);
		i += 2;
	}
	if (stop == 0)
		ft_builtin_exit(data, command);
	if (stop == 1 && data->exit_code == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_quit(data, 0);
	}
}
