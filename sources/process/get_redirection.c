/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:42:33 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/12 10:58:20 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_rediction(t_data *data, int i)
{
	t_data		*tmp;
	t_pipeline	*pipe;

	tmp = data;
	while (i > 0)
	{
		tmp->cmd = tmp->cmd->next;
		i--;
	}
	pipe = s_read_cnt(tmp->cmd);
	ft_extract_inputredir(data, pipe);
	ft_extract_outputredir(data, pipe);
}

// cat valgrind_ignore_leaks.txt < aaaa > bbbbb << cccc >> ddddd
