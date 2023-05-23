/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_chevrons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:48:52 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/23 10:39:18 by mvogel           ###   ########lyon.fr   */
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
	while (*i <= (int)ft_strlen(pipe) && pipe[*i] != symbol)
	{
		new[(*j)++] = pipe[(*i)++];
	}
	return ;
}

static char	*chevrons_handler(char *pipe)
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

void	space_chevron(t_data *data, char **pipes_tab)
{
	int	i;

	i = 0;
	while (pipes_tab[i])
	{
		pipes_tab[i] = chevrons_handler(pipes_tab[i]);
		if (!pipes_tab[i])
			return (free_tab(pipes_tab), ft_quit(data, 12));
		i++;
	}
	return ;
}
