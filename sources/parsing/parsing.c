/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/15 16:58:37 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_chain(t_data *data)
{
	t_list	*cp;
	int		i;

	i = 0;
	cp = data->cmd;
	while (cp)
	{
		i = 0;
		while (s_read_cnt(cp)->command[i])
		{
			printf("%s ", s_read_cnt(cp)->command[i]);
			i++;
		}
		if (i > 1)
			printf("\n");
		cp = cp->next;
	}
	printf("\n");
	return ;
}

void	print_tab(char **pipe_tab)
{
	int i = 0;

	while (pipe_tab[i])
	{
		printf("tab[%d] : %s\n", i, pipe_tab[i]);
		i++;
	}
	return ;
}

////////////////////////////////////////////////////////////////////////////////

char	**parsing_token(char *pipe)
{
	char	**token_tab;

	token_tab = NULL;
	token_tab = split_tokens(pipe, " \t");
	// token_tab = parsingredirectionsJulien;
	token_tab = trim_quotes(token_tab);
	return (token_tab);
}

void	create_chain(t_list **cmd, void *content)
{
	if (*cmd == NULL)
		*cmd = ft_lstnew(content);
	else
		ft_lstadd_back(cmd, ft_lstnew(content));
	return ;
}

void	split_tab(t_list **cmd, char **pipe_tab)
{
	int		i;
	char	**token_tab;
	void	*adress;

	i = 0;
	token_tab = NULL;
	while (pipe_tab[i])
	{
		token_tab = parsing_token(pipe_tab[i]);
		if (!token_tab)
			return (perror("Error\n"), free(pipe_tab));
		adress = s_init(token_tab, NULL, NULL);
		create_chain(cmd, adress);
		i++;
	}
	free_tab(pipe_tab);
}

int	parsing(t_data *data, char *input)
{
	char	**pipe_tab;
	int		nb_p;

	nb_p = nb_pipes(input);
	pipe_tab = NULL;
	pipe_tab = create_tab(pipe_tab, input, nb_p);
	expands(data, pipe_tab);
	// print_tab(pipe_tab);
	if (pipe_tab[0][0] != '\0')
	{
		space_chevron(pipe_tab);
		split_tab(&data->cmd, pipe_tab);
		return (0);
	}
	// print_chain(data);
	return (1);
}
