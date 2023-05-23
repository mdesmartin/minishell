/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:23:18 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/23 10:38:08 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	is_whitespace_or_end(char c, char *str, int i)
{
	int	a;

	a = 2;
	while (i != 0 && str[i] && a)
	{
		i--;
		a--;
	}
	if (!a && (c == '\"' && str[i] == '\"'))
		return (1);
	else if (c == ' ' || c == '\t' || c == '\0')
		return (1);
	else
		return (0);
}

int	is_in_quotes(char *str, int index)
{
	int		i;
	int		start;
	char	quote;

	i = 0;
	start = 0;
	while (i <= index)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			start = i;
			i++;
			while (str[i] != quote)
				i++;
			if (index > start && index < i)
				return (1);
		}
		i++;
	}
	return (0);
}
