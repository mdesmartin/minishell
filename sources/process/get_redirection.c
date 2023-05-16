/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:42:33 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/16 14:36:35 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_redirection(t_data *data, char **cmd, char **input, char **output)
{
	ft_extract_inputredir(data, cmd, input);
	ft_extract_outputredir(data, cmd, output);
}

// void	get_redirection(t_data *data)
// {
// 	t_list		*tmp;
// 	t_pipeline	*pipe;

// 	tmp = data->cmd;
// 	while (tmp)
// 	{
// 		pipe = s_read_cnt(tmp);
// 		ft_extract_inputredir(data, pipe);
// 		ft_extract_outputredir(data, pipe);
// 		tmp = tmp->next;
// 	}
// }

char	**ft_redirection(t_data *data, int i)
{
	t_list	*tmp;
	char	**input;
	char	**output;

	tmp = data->cmd;
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	input = (char **)s_read_cnt(tmp)->input;
	output = (char **)s_read_cnt(tmp)->output;
	ft_input_redirection(data, input);
	ft_output_redirection(data, output);
	return ((char **)s_read_cnt(tmp)->command);
}
