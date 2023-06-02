/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:56:56 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/02 12:45:43 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// redirections[0]: 0 = < ; 1 = <<
// redirections[1]: file redirections[0] == 0, limiter redirections[0] == 1
// redirections[0]: 2 = > ; 3 = >>
// redirections[1]: trunc redirections[0] == 2, append redirections[0] == 3

static void	ft_output_file(t_data *data, char *file, int *nb_output)
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
	if (*nb_output != 1)
	{
		(*nb_output)--;
		ft_close(outfile);
		return ;
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, outfile);
		ft_error(data, "Error while duplicating file descriptor", 1);
	}
	ft_close(outfile);
}

static void	ft_output_appends(t_data *data, char *file, int *nb_output)
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
	if (*nb_output != 1)
	{
		(*nb_output)--;
		ft_close(outfile);
		return ;
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, outfile);
		ft_error(data, "Error while duplicating file descriptor", 1);
	}
	ft_close(outfile);
}

static void	ft_input_file(t_data *data, char *file, int *nb_input)
{
	char	*msg;
	int		infile;

	infile = open(file, O_RDONLY, 0644);
	if (infile == -1)
	{
		msg = ft_strjoin("minishell: ", file);
		if (!msg)
			ft_error(data, "Error when creating error message", 12);
		perror(msg);
		free(msg);
		ft_quit(data, 1);
	}
	if (*nb_input != 1)
	{
		(*nb_input)--;
		ft_close(infile);
		return ;
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		ft_close_fds(data, infile);
		ft_error(data, "Error while duplicating file descriptor", 1);
	}
	ft_close(infile);
}

static void	ft_get_nb_redirec(char **tab, int *nb_input, int *nb_output)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '0' || tab[i][0] == '1')
			(*nb_input) += 1;
		else if (tab[i][0] == '2' || tab[i][0] == '3')
			(*nb_output) += 1;
		i += 2;
	}
}

void	ft_apply_redirection(t_data *data, t_pipeline *pipe,
		char **redirections)
{
	int	nb_input;
	int	nb_output;
	int	i;

	i = 0;
	nb_input = 0;
	nb_output = 0;
	ft_get_nb_redirec(redirections, &nb_input, &nb_output);
	while (redirections[i] && redirections[i + 1])
	{
		ft_check_redir(data, redirections[i + 1]);
		if (redirections[i][0] == '0')
			ft_input_file(data, redirections[i + 1], &nb_input);
		else if (redirections[i][0] == '1')
			ft_dup2_here_doc(data, pipe, &nb_input);
		else if (redirections[i][0] == '2')
			ft_output_file(data, redirections[i + 1], &nb_output);
		else if (redirections[i][0] == '3')
			ft_output_appends(data, redirections[i + 1], &nb_output);
		i += 2;
	}
}
