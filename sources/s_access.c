/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_access.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:01:03 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/30 16:40:41 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*s_convert_content(void *content)
{
	if (!content)
		return (NULL);
	return (content);
}

// EXEMPLE : data->cmd->content	-become->		s_read_cnt(data->cmd)->command
t_pipeline	*s_read_cnt(t_list *cmd)
{
	if (!cmd->content)
		return (NULL);
	return (cmd->content);
}

void	*s_init(char **command, char **input, char **output)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);

	pipeline->command = command;
	if (!input)
		pipeline->input = ft_calloc(2, sizeof(char*));//terminer dinit la structure puis modif dand split tab, compile, test dollar, add ><<<>> when init
	if (!output)
		pipeline->output = ft_calloc(2, sizeof(char*));
	return (pipeline);		
}



// (echo)->("bonjour mehdi")->(|)->(echo)