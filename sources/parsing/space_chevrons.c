/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_chevrons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:48:52 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/01 16:40:25 by mvogel           ###   ########lyon.fr   */
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

void	space_chevron(t_data *data, char **pipes_tab, int nb_pipes)
{
	int	i;

	i = 0;
	while (nb_pipes)// && pipes_tab[i])
	{
		if (pipes_tab[i][0])
			pipes_tab[i] = chevrons_handler(pipes_tab[i]);
		if (!pipes_tab[i])
		{
			free_tab(pipes_tab);
			ft_error(data, "Memory allocation failed: chevrons_handler", 12);
		}
		i++;
		nb_pipes--;
	}
	return ;
}
