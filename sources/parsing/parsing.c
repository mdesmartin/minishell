/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/31 17:11:32 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	print_chain(t_data *data)
// {
// 	t_list	*cp;
// 	int		i;

// 	i = 0;
// 	cp = data->cmd;
// 	printf("chain start:");
// 	while (cp)
// 	{
// 		i = 0;
// 		while (s_read_cnt(cp)->command[i])
// 		{
// 			printf("%s ", s_read_cnt(cp)->command[i]);
// 			i++;
// 		}
// 		if (i > 1)
// 			printf("\n");
// 		cp = cp->next;
// 	}
// 	printf(":end");
// 	printf("\n");
// 	return ;
// }

// void	print_tab(char **pipes_tab)
// {
// 	int i = 0;

// 	while (pipes_tab[i])
// 	{
// 		printf("tab[%d] :%s:end\n", i, pipes_tab[i]);
// 		i++;
// 	}
// 	return ;
// }

//////

///// $s|""|ls qui marche pas ainsi que $s |$d

static void	create_link(t_list **cmd, void *content)
{
	if (*cmd == NULL)
		*cmd = ft_lstnew(content);
	else
		ft_lstadd_back(cmd, ft_lstnew(content));
	return ;
}

static void	create_chain(t_data *data, t_list **cmd, char **pipes_tab, int nb_pipes)
{
	char	**token_tab;
	char	**redirections;
	void	*adress;
	int		i;

	i = 0;
	while (pipes_tab[i])
	{
		if (pipes_tab[i][0] != '\0')
		{
			token_tab = split_tokens(data, pipes_tab, pipes_tab[i], " \t");
			token_parsing(token_tab);
			redirections = ft_extract_redirections(data, token_tab, pipes_tab);
			adress = s_init(token_tab, redirections);
			if (!adress)
				return (free_tab(pipes_tab), free_tab(token_tab),
					free_tab(redirections), ft_quit(data, 12));
			create_link(cmd, adress);
		}
		nb_pipes--;
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
		return (ft_quit(data, 12), 1);
	expands(data, pipes_tab);
	if (nb_pipes)
	{
		space_chevron(data, pipes_tab, nb_pipes);
		create_chain(data, &data->cmd, pipes_tab, nb_pipes);
		if (!data->cmd)
			return (1);
		return (0);
	}
	return (1);
}
