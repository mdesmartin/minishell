/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:33:28 by mvogel            #+#    #+#             */
/*   Updated: 2023/05/01 23:18:50 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_quote(char *input, int *i, char quote)
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

int	find_pipe(char *input, int *i)
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

int	nb_pipes(char *input)
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

char	**split_pipes(char **pipe_tab, int nb_p, char *input)
{
	int	start;
	int	len_pipe;
	int	i;
	int	j;

	start = 0;
	len_pipe = 0;
	i = 0;
	j = 0;
	while (nb_p)
	{
		find_pipe(input, &i);
		len_pipe = i - start;
		pipe_tab[j] = ft_substr(input, start, len_pipe);
		if (!pipe_tab[j])
			return (ft_putstr_fd("error creating tab\n", 2), NULL);
		j++;
		i++;
		start = i;
		nb_p--;
	}
	pipe_tab[j] = NULL;
	return (pipe_tab);
}

char	**create_tab(char **pipe_tab, char *input, int nb_pipe)
{
	pipe_tab = NULL;
	pipe_tab = ft_calloc(sizeof(char *), (nb_pipe + 1));
	if (!pipe_tab)
		return (ft_putstr_fd("error creating tab\n", 2), NULL);
	pipe_tab = split_pipes(pipe_tab, nb_pipe, input);
	return (pipe_tab);
}
