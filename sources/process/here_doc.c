/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:00:26 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/25 16:10:44 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_exitcode;

static int	ft_here_doc(t_data *data, t_pipeline *pipe, char *limiter)
{
	char	*input;
	int		limiter_len;
	int		intput_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		input = readline("here_doc> ");
		if (!input)
			return (ft_error_heredoc(data, pipe->here_doc_fd, limiter));
		if (g_exitcode == 1 || g_exitcode == 3)
			return (ft_stop_heredoc(data, pipe->here_doc_fd, input));
		intput_len = ft_strlen(input);
		if (ft_strncmp(input, limiter, limiter_len) == 0
			&& intput_len == limiter_len)
			break ;
		input = ft_here_doc_expand(data, pipe, input);
		intput_len = ft_strlen(input);
		if (write(pipe->here_doc_fd[1], input, intput_len) == -1
			|| write(pipe->here_doc_fd[1], "\n", 1) == -1)
			ft_perror(data, "Error while writing in the here_doc's pipe!", 1);
		free(input);
	}
	free(input);
	return (0);
}

static int	ft_input_heredoc(t_data *data, t_pipeline *pip,
		char *limiter, int nb_input)
{
	if (pipe(pip->here_doc_fd) == -1)
		ft_error(data, "Pipe failed for here_doc!", 1);
	ft_check_hd_expand(pip, limiter);
	signal_init(signal_heredoc);
	if (ft_here_doc(data, pip, limiter) == 1)
		return (1);
	signal_init(signal_handler);
	ft_close(pip->here_doc_fd[1]);
	if (nb_input != 1)
		ft_close(pip->here_doc_fd[0]);
	return (0);
}

static int	ft_get_nb_input(char **tab)
{
	int	nb_input;
	int	i;

	i = 0;
	nb_input = 0;
	while (tab[i])
	{
		if (tab[i][0] == '0' || tab[i][0] == '1')
			nb_input++;
		i += 2;
	}
	return (nb_input);
}

static int	ft_get_here_doc(t_data *data, t_pipeline *pipe)
{
	int	nb_input;
	int	i;

	i = 0;
	nb_input = ft_get_nb_input(pipe->redirections);
	while (pipe->redirections[i] && pipe->redirections[i + 1])
	{
		if (pipe->redirections[i][0] == '0')
			nb_input--;
		else if (pipe->redirections[i][0] == '1')
		{
			if (ft_input_heredoc(data, pipe, pipe->redirections[i + 1],
					nb_input) == 1)
				return (1);
			nb_input--;
		}
		i += 2;
	}
	return (0);
}

int	ft_process_here_doc(t_data *data)
{
	t_pipeline	*pipe;
	t_list		*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		pipe = s_read_cnt(tmp);
		if (ft_get_here_doc(data, pipe) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
