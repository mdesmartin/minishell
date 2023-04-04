/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:06:52 by julien            #+#    #+#             */
/*   Updated: 2023/04/04 11:14:02 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// input[0] : 0 = < ; 1 = <<
// input[1] : file or limiter
static void	ft_input_file(t_data *data)
{
	int	infile;

infile = open("env.txt", O_RDONLY, 0644);
	// infile = open((char *)s_read_cnt(data->cmd)->input[0], O_RDONLY, 0644);
	if (infile == -1)
		perror("Error when opening file1! ");
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		ft_close_fds(data);
		close(infile);
		perror("Error while duplicating file descriptor! ");
		ft_quit(data);
		exit (1);
	}
}

static void	ft_here_doc(t_data *data, int *here_doc_fd, char *limiter)
{
	char	*input;
	int		limiter_len;
	int		intput_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		input = readline("here_doc> ");
		if (!input)
		{
			close(here_doc_fd[0]);
			close(here_doc_fd[1]);
			free(here_doc_fd);
			ft_error(data, "Error while using here_doc");
		}
		intput_len = ft_strlen(input);
		if (ft_strncmp(input, limiter, limiter_len) == 0
			&& intput_len == limiter_len)
			break ;
		if (write(here_doc_fd[1], input, intput_len) == -1
			|| write(here_doc_fd[1], "\n", 1) == -1)
			perror("Error while writing in the here_doc's pipe!");
		free(input);
	}
	free(input);
}

static void	ft_input_heredoc(t_data *data)
{
	char	limiter[5] = "STOP";
	// char	*limiter;
	int		*here_doc_fd;

	// limiter = (char *)s_read_cnt(data->cmd)->input[1];
	here_doc_fd = ft_calloc(3, sizeof(int *));
	if (!here_doc_fd)
		ft_error(data, "Memory allocating failed for here_doc_fd");
	if (pipe(here_doc_fd) == -1)
	{	
		free(here_doc_fd);
		ft_error(data, "Pipe failed for here_doc!");
	}
	ft_here_doc(data, here_doc_fd, limiter);
	close(here_doc_fd[1]);
	if (dup2(here_doc_fd[0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data);
		close(here_doc_fd[0]);
		free(here_doc_fd);
		ft_error(data, "Error while duplicating file descriptor! ");
	}
	close(here_doc_fd[0]);
}

void	ft_input_redirection(t_data *data)
{
	if (!(char *)s_read_cnt(data->cmd)->input[0])
		return ;
	else if ((char)s_read_cnt(data->cmd)->input[0][0] == '0')
		ft_input_file(data);
	else if ((char)s_read_cnt(data->cmd)->input[0][0] == '1')
		ft_input_heredoc(data);
}

// static void	ft_here_doc(t_data *data, int *here_doc_fd, char *limiter)
// {
// 	char	*tmp;
// 	int		limiter_len;
// 	int		intput_len;

// 	limiter_len = ft_strlen(limiter);
// 	while (1)
// 	{
// 		printf("here_doc> ");
// 		tmp = get_next_line(STDIN_FILENO);
// 		if (!tmp)
// 		{
// 			perror("Error while using here_doc");
// 			close(here_doc_fd[1]);
// 			ft_quit(data);
// 			exit(1);
// 		}
// 		intput_len = ft_strlen(tmp);
// 		if (ft_strncmp(tmp, limiter, limiter_len) == 0
// 			&& intput_len - 1 == limiter_len)
// 			break ;
// 		if (write(here_doc_fd[1], tmp, intput_len) == -1)
// 			perror("Error while writing in the here_doc's pipe!");
// 		free(tmp);
// 	}
// 	free(tmp);
// }
