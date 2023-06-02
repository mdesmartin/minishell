/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:42:13 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/02 16:25:19 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_redirection(t_data *data, int i)
{
	t_pipeline	*pipe;
	t_list		*tmp;

	tmp = data->cmd;
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	pipe = s_read_cnt(tmp);
	ft_apply_redirection(data, pipe, pipe->redirections);
	return (pipe->command);
}

void	ft_check_redir(t_data *data, char *redirection)
{
	if (redirection[0] == -44)
	{
		redirection[0] = '$';
		if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
			ft_error(data, "Error while duplicating file descriptor", 1);
		printf("minishell: %s: ambiguous redirect\n", redirection);
		ft_quit(data, 1);
	}
}
