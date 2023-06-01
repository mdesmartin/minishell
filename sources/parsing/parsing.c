/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/01 10:58:08 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	create_link(t_list **cmd, void *content)
{
	if (*cmd == NULL)
		*cmd = ft_lstnew(content);
	else
		ft_lstadd_back(cmd, ft_lstnew(content));
	return ;
}

static void	create_chain(t_data *data, t_list **cmd, char **pipes_tab)
{
	char	**token_tab;
	char	**redirections;
	void	*adress;
	int		i;

	i = 0;
	while (pipes_tab[i])
	{
		token_tab = split_tokens(data, pipes_tab, pipes_tab[i], " \t");
		token_parsing(token_tab);
		redirections = ft_extract_redirections(data, token_tab, pipes_tab);
		adress = s_init(token_tab, redirections);
		if (!adress)
		{
			free_tab(pipes_tab);
			free_tab(token_tab);
			free_tab(redirections);
			ft_error(data, "Memory allocation failed: creat_chain", 12);
		}
		create_link(cmd, adress);
		i++;
	}
	free_tab(pipes_tab);
}

int	parsing(t_data *data, char *input)
{
	char	**pipes_tab;
	int		nb_pipes;

	nb_pipes = count_pipes(input);
	pipes_tab = NULL;
	pipes_tab = split_pipes(pipes_tab, input, nb_pipes);
	if (!pipes_tab)
		ft_error(data, "Memory allocation failed: pipes_tab in parsing", 12);
	expands(data, pipes_tab);
	if (pipes_tab[0][0] != '\0')
	{
		space_chevron(data, pipes_tab);
		create_chain(data, &data->cmd, pipes_tab);
		return (0);
	}
	return (1);
}
