/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:33:28 by mvogel            #+#    #+#             */
/*   Updated: 2023/05/23 10:22:41 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	find_quote(char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] != '\0')
	{
		if (input[*i] == quote)
			return (0);
		(*i)++;
	}
	return (-1);
}

static int	find_pipe(char *input, int *i)
{
	while (input[*i] != '\0')
	{
		if (input[*i] == '\'')
		{
			if (find_quote(input, i, '\'') == -1)
				return (-1);
		}
		if (input[*i] == '\"')
		{
			if (find_quote(input, i, '\"') == -1)
				return (-1);
		}
		if (input[*i] == '|')
			return (1);
		(*i)++;
	}
	return (0);
}

int	count_pipes(char *input)
{
	int	nb_pipes;
	int	j;
	int	n;

	j = 0;
	n = 1;
	nb_pipes = 0;
	while (n && n != -1)
	{
		n = find_pipe(input, &j);
		nb_pipes++;
		j++;
	}
	if (n == -1)
		return (-1);
	return (nb_pipes);
}

static char	**create_tab(char **pipes_tab, int nb_pipes, char *input)
{
	int	start;
	int	len_pipe;
	int	i;
	int	j;

	start = 0;
	len_pipe = 0;
	i = 0;
	j = 0;
	while (nb_pipes)
	{
		find_pipe(input, &i);
		len_pipe = i - start;
		pipes_tab[j] = ft_substr(input, start, len_pipe);
		if (!pipes_tab[j])
			return (NULL);
		j++;
		i++;
		start = i;
		nb_pipes--;
	}
	pipes_tab[j] = NULL;
	return (pipes_tab);
}

char	**split_pipes(char **pipes_tab, char *input, int nb_pipes)
{
	pipes_tab = NULL;
	pipes_tab = ft_calloc(sizeof(char *), (nb_pipes + 1));
	if (!pipes_tab)
		return (NULL);
	pipes_tab = create_tab(pipes_tab, nb_pipes, input);
	if (!pipes_tab)
		return (free_tab(pipes_tab), NULL);
	return (pipes_tab);
}
