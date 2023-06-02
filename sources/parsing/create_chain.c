/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_chain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:52:58 by mvogel            #+#    #+#             */
/*   Updated: 2023/06/02 16:12:56 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	something_in_token(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '\0')
		return (0);
	else
		return (1);
}

static int	something_in_tab(char **input)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (input[i])
	{
		if (something_in_token(input[i]))
			flag = 1;
		i++;
	}
	return (flag);
}

static void	create_link(t_list **cmd, void *content)
{
	t_list	*new;

	new = NULL;
	if (*cmd == NULL)
		*cmd = ft_lstnew(content);
	else
	{
		new = ft_lstnew(content);
		ft_lstadd_back(cmd, new);
	}
}

static int	creating_pipeline(void **adress, t_data *data, \
char	**token_tab, char **pipes_tab)
{
	char	**redirections;

	redirections = ft_extract_redirections(data, token_tab, pipes_tab);
	*adress = s_init(token_tab, redirections);
	if (!*adress)
	{
		free_tab(pipes_tab);
		free_tab(token_tab);
		free_tab(redirections);
		error_mem(data);
		return (1);
	}
	return (0);
}

void	create_chain(t_data *data, t_list **cmd, \
char **pipes_tab, int nb_pipes)
{
	char	**token_tab;
	void	*adress;
	int		i;

	i = 0;
	adress = NULL;
	while (nb_pipes)
	{
		if (!pipes_tab[i][0])
			pipes_tab[i][0] = -43;
		token_tab = split_tokens(data, pipes_tab, pipes_tab[i], " \t");
		token_parsing(token_tab);
		if (something_in_tab(token_tab))
		{
			if (creating_pipeline(&adress, data, token_tab, pipes_tab))
				return ;
			create_link(cmd, adress);
		}
		else
			free_tab(token_tab);
		nb_pipes--;
		i++;
	}
	free_tab(pipes_tab);
}
