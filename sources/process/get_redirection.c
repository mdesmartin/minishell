/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:42:33 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/13 13:38:14 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_rediction(t_data *data, int i)
{
	t_list		*tmp;
	t_pipeline	*pipe;

	tmp = data->cmd;
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	pipe = s_read_cnt(tmp);
	ft_extract_inputredir(data, pipe);
	ft_extract_outputredir(data, pipe);
}

char	**ft_redirection(t_data *data, int i)
{
	t_list	*tmp;

	tmp = data->cmd;
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	ft_input_redirection(data, (char **)s_read_cnt(tmp)->input);
	ft_output_redirection(data, (char **)s_read_cnt(tmp)->output);
	return ((char **)s_read_cnt(tmp)->command);
}

// cat valgrind_ignore_leaks.txt < aaaa > bbbbb << cccc >> ddddd
