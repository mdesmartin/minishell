/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:42:13 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/02 12:58:29 by jmoutous         ###   ########lyon.fr   */
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
	if (redirection[0] == 0)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		ft_quit(data, 1);
	}
}
