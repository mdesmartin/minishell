/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_chevrons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:48:52 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/16 15:41:47 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_chevrons(char *pipe, char *new, int *i, int *j)
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

void	get_quote(char *pipe, char *new, int *i, int *j)
{
	char	symbol;

	symbol = pipe[*i];
	(*i)++;
	new[(*j)++] = symbol;
	while (*i <= (int)ft_strlen(pipe) && pipe[*i] != symbol)
	{
		new[(*j)++] = pipe[(*i)++];
	}
	return ;
}

char	*chevrons_handler(char *pipe)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc(ft_strlen(pipe) * 3, sizeof(char));
	if (!new)
		return (NULL);
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
		if (pipe[i])
			i++;
	}
	free(pipe);
	return (new);
}

char	**space_chevron(char **pipe_tab)
{
	int	i = 0;

	while (pipe_tab[i])
	{
		pipe_tab[i] = chevrons_handler(pipe_tab[i]);
		if (!pipe_tab[i])
			return (free_tab(pipe_tab), NULL);
		i++;
	}
	return (pipe_tab);
}

