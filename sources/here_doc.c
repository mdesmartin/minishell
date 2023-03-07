/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:16:46 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/07 13:46:12 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_here_doc(t_data *data)
{
	char	*tmp;
	int		here_doc_fd;
	int		limiter_len;
	int		intput_len;

	if (pipe(here_doc_fd) == -1)
		ft_error(data, "Pipe failed for here_doc!");
	limiter_len = ft_strlen(data->limiter);
	while (1)
	{
		ft_printf("here_doc> ");
		tmp = get_next_line(STDIN_FILENO);
		if (!tmp)
			ft_error(data, "Error while using here_doc");
		intput_len = ft_strlen(tmp);
		if (ft_strncmp(tmp, data->limiter, limiter_len) == 0
			&& intput_len - 1 == limiter_len)
			break ;
		if (write(data->here_doc_fd[1], tmp, intput_len) == -1)
			perror("Error while writing in the here_doc's pipe!");
		free(tmp);
	}
	free(tmp);
}