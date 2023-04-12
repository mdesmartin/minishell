/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:33:28 by mvogel            #+#    #+#             */
/*   Updated: 2023/04/12 13:58:32 by mehdidesmar      ###   ########lyon.fr   */
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

int	find_separator(char *input, int *i, char separator)
{
	int end;

	end = 0;
	while (input[*i] != '\0')
	{
		if (input[*i] == '\'')
			if (find_quote(input, i, '\'') == -1)
				return (-1);
		if (input[*i] == '\"')
			if (find_quote(input, i, '\"') == -1)
				return (-1);
		if (input[*i] == separator)
		{
			end = *i;
			while (input[*i] == separator)
				(*i)++;
			(*i)--;
			return (end);
		}
		(*i)++;
	}
	return (0);
}

int	nb_pipes(char *input, char separator)
{
	int	nb_pipes;
	int	j;
	int	n;

	j = 0;
	n = 1;
	nb_pipes = 0;
	while (n && n != -1)
	{
		n = find_separator(input, &j, separator);
		nb_pipes++;
		j++;
	}
	if (n == -1)
		return (-1);
	return (nb_pipes);
}

char	**split_pipes(char **pipe_tab, int nb_p, char *input, char separator)
{
	int	start;
	int	len_pipe;
	int	i;
	int	j;

	start = 0;
	len_pipe = 0;
	i = 0;
	j = 0;
	while (input[i] && input[i] == separator)
		i++;
	start = i;
	while (j < nb_p)
	{
		len_pipe = find_separator(input, &i, separator) - start;
		pipe_tab[j] = ft_substr(input, start, len_pipe);
		if (!pipe_tab[j])
			return (ft_putstr_fd("error creating tab\n", 2), NULL);
		i++;
		start = i;
		j++;
	}
	pipe_tab[j] = NULL;
	return (pipe_tab);
}

char	**create_tab(char **pipe_tab, char *input, int nb_pipe)
{
	printf("nb_pipe first : %d\n", nb_pipe);
	pipe_tab = NULL;
	pipe_tab = ft_calloc(sizeof(char *), (nb_pipe + 1));
	if (!pipe_tab)
		return (ft_putstr_fd("error creating tab\n", 2), NULL);
	pipe_tab = split_pipes(pipe_tab, nb_pipe, input, '|');
	return (pipe_tab);
}
