/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_chevrons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:48:52 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/05 14:01:54 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_chevrons(char *pipe, char *new, int *i, int *j)
{
	new[(*j)++] = ' ';
	new[(*j)++] = pipe[(*i)++];
	if (pipe[*i] && (pipe[*i] == '<' || pipe[*i] == '>'))
		new[(*j)++] = pipe[(*i)];
	else
		(*i)--;
	new[(*j)] = ' ';
	return ;
}

static void	get_quote(char *pipe, char *new, int *i, int *j)
{
	char	symbol;

	symbol = pipe[*i];
	(*i)++;
	new[(*j)++] = symbol;
	while (pipe[*i] != symbol)
	{
		new[(*j)++] = pipe[(*i)++];
	}
	return ;
}

char	*space_chevrons(char *pipe)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(pipe) * 3, sizeof(char));
	i = 0;
	j = 0;
	while (pipe[i])
	{
		if (pipe[i] == '\'' || pipe[i] == '\"')
			get_quote(pipe, new, &i, &j);
		if (pipe[i] == '<' || pipe[i] == '>')
			get_chevrons(pipe, new, &i, &j);
		else
			new[j] = pipe[i];
		j++;
		i++;
	}
	free(pipe);
	return (new);
}
