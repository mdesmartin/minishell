/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:33:28 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/27 17:10:29 by mvogel           ###   ########lyon.fr   */
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

int	split_pipes(t_data *data, int nb_p, char *input)
{
	char	**pipe;
	int		start;
	int		len_pipe;
	int		i;

	start = 0;
	len_pipe = 0;
	i = 0;
	while (nb_p)
	{
		find_pipe(input, &i);
		len_pipe = i - start;
		pipe = ft_calloc(sizeof(char *), 2);
		pipe[0] = ft_substr(input, start, len_pipe);
		if (!pipe)
			return (-1);
		create_chain(data->cmd, &pipe);
		i++;
		start = i;
		nb_p--;
	}
	return (0);
}
