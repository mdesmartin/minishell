/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:59:47 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/05 14:06:09 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*whitespace_handler(char *pipes_tab, int *start, int end)
{
	if (ft_strncmp("echo", pipes_tab, 5))
		return (pipes_tab);
	else
		return (trim_from_to(pipes_tab, start, end));
}

int	heredoc_before(char *line, int i)
{
	i--;
	while (i >= 0 && line[i] && ft_isalnum(line[i]))
		i--;
	while (i >= 0 && line[i] && (line[i] == ' ' || line[i] == '\t'))
		i--;
	if (i >= 0 && line[i] == '<')
	{
		i--;
		if (i >= 0 && line[i] && line[i] == '<')
			return (1);
	}
	return (0);
}

int	lonely_expand_in_quote(char *str, int i, char c)
{
	int	a;
	int	start;

	a = 2;
	start = i - 1;
	while (i != 0 && str[i] && a)
	{
		i--;
		a--;
	}
	if (!a && (c == '\"' && str[i] == '\"') && is_in_quotes(str, start))
		return (1);
	else
		return (0);
}

int	chevron_before(char *pipes_tab, int *start)
{
	int	i;

	i = *start - 2;
	while (i >= 0 && (pipes_tab[i] == ' ' || pipes_tab[i] == '\t'))
		i--;
	if (i >= 0 && (pipes_tab[i] == '>' || pipes_tab[i] == '<'))
	{
		pipes_tab[*start - 1] = -44;
		return (1);
	}
	return (0);
}

int	convert_quote(char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == '\'')
			value[i] = -39;
		else if (value[i] == '\"')
			value[i] = -34;
		i++;
	}
	return (1);
}
