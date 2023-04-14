/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:48:52 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/04/14 13:18:16 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_chevron(char *pipe, char *new, int *i, int *j)
{
	int twin;
	
	twin = 1;

	(*i)++;
	if (pipe[*i] && (pipe[*i] == '<' || pipe[*i] == '>'))
		twin = 2;
	else
		(*i)--;
	new[(*j)++] = ' ';
	while (twin--)
		new[(*j)++] = pipe[(*i)];
	new[(*j)] = ' ';
	return ;
}

void	get_quote(char *pipe, char *new, int *i, int *j)
{
	char symbol;

	symbol = pipe[*i];
	(*i)++;
	new[(*j)++] = symbol;
	while (pipe[*i] != symbol)
	{
		new[(*j)++] = pipe[(*i)++];
	}
	return ;
}

char	*space_chevron(char *pipe)
{
	char *new;
	int i;
	int j;
	
	new = ft_calloc(ft_strlen(pipe) * 3, sizeof(char));
	i = 0;
	j = 0;
	while (pipe[i])
	{
		if (pipe[i] == '\'' || pipe[i] == '\"')
			get_quote(pipe, new, &i, &j);
		if (pipe[i] == '<' || pipe[i] == '>')
			get_chevron(pipe, new, &i, &j);
		else
			new[j] = pipe[i];
		j++;
		i++;
	}
	free(pipe);
	return (new);
}
