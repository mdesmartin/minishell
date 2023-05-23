/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_access.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:01:03 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/19 15:41:01 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	**calloc_tab(void)
{
	char	**tab;

	tab = ft_calloc(3, sizeof(char *));
	tab[0] = ft_calloc(2, sizeof(char *));
	tab[1] = ft_calloc(2, sizeof(char *));
	return (tab);
}

void	*s_init(char **command, char **redirections)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (pipeline == NULL)
		return (NULL);
	if (!command)
		pipeline->command = calloc_tab();
	else
		pipeline->command = command;
	if (!redirections)
		pipeline->redirections = calloc_tab();
	else
		pipeline->redirections = redirections;
	return (pipeline);
}
