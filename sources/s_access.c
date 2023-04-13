/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_access.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:01:03 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/04/13 15:33:16 by jmoutous         ###   ########lyon.fr   */
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

char	**calloc_tab()
{
	char	**tab;

	tab = ft_calloc(3, sizeof(char*));
	tab[0] = ft_calloc(2, sizeof(char*));
	tab[1] = ft_calloc(2, sizeof(char*));
	return (tab);
}

void	*s_init(char **command, char **input, char **output)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);

	if (!command)
		pipeline->command = calloc_tab();// ft_calloc(2, sizeof(char*));
	else
		pipeline->command = command;

	if (!input)
		pipeline->input = output;
		// pipeline->input = calloc_tab();//terminer dinit la structure puis modif dand split tab, compile, test dollar, add ><<<>> when init
	if (!output)
		pipeline->output = input;
		// pipeline->output = calloc_tab();
	return (pipeline);		
}



// (echo)->("bonjour mehdi")->(|)->(echo)