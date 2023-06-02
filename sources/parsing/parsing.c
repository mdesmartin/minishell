/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/02 14:26:04 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_chain(t_data *data)
{
	t_list *cp;
	int i = 0;

	cp = data->cmd;
	ft_printf("the parsed input is :");
	while (cp)
	{
		i = 0;
		while (s_read_cnt(cp)->command[i])
		{
			printf("%s-", s_read_cnt(cp)->command[i]);
			i++;
		}
		// if (i > 1)
			// printf("");
		cp = cp->next; 
	}
	printf(":\n");
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
	if (nb_pipes)
	{
		space_chevron(data, pipes_tab, nb_pipes);
		create_chain(data, &data->cmd, pipes_tab, nb_pipes);
		print_chain(data);
		if (!data->cmd)
			return (1);
		return (0);
	}
	return (1);
}
