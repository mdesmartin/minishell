/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_access.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:01:03 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/29 16:53:47 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*s_convert_content(void *content)
{
	if (!content)
		return (NULL);
	return (content);
}

// EXEMPLE : data->cmd->content		-become->		s_access_content(data->cmd)->command
t_pipeline	*s_access_content(t_list *cmd)
{
	if (!cmd->content)
		return (NULL);
	return (cmd->content);
}

// void	s_replace_command(t_data *data, char **new_command)
// {
// 	t_pipeline new_pipeline;

// 	new_pipeline.command = new_command;
// 	new_pipeline.input = s_access_content(data->cmd)->input;
// 	new_pipeline.output = s_access_content(data->cmd)->output;
// 	data->cmd = &new_pipeline;
// 	return ;
// }


// (echo)->("bonjour mehdi")->(|)->(echo)