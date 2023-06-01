/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_access.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:01:03 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/01 11:13:53 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipeline	*s_convert_content(void *content)
{
	if (!content)
		return (NULL);
	return (content);
}

t_pipeline	*s_read_cnt(t_list *cmd)
{
	if (!cmd->content)
		return (NULL);
	return (cmd->content);
}

static void	*ft_free_pipe(t_pipeline *pipeline)
{
	if (pipeline->command)
		free(pipeline->command);
	if (pipeline->redirections)
		free(pipeline->redirections);
	free(pipeline);
	return (NULL);
}

static char	**calloc_tab(void)
{
	char	**tab;

	tab = ft_calloc(3, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = ft_calloc(2, sizeof(char *));
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	tab[1] = ft_calloc(2, sizeof(char *));
	if (!tab[1])
	{
		free(tab[0]);
		free(tab);
		return (NULL);
	}
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
	if (!pipeline->command)
		return (ft_free_pipe(pipeline));
	if (!redirections)
		pipeline->redirections = calloc_tab();
	else
		pipeline->redirections = redirections;
	if (!pipeline->redirections)
		return (ft_free_pipe(pipeline));
	pipeline->here_doc_fd[0] = 0;
	pipeline->here_doc_fd[1] = 0;
	return (pipeline);
}
