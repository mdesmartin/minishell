/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:23:18 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/05 13:46:12 by mehdidesmar      ###   ########lyon.fr   */
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

int	is_whitespace_or_end(char c)
{
	if (c == ' ' || c == '\t' || c == '\0' || c == '\"')
		return (1);
	else
		return (0);
}

int	in_quotes(char *str, int index)
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
