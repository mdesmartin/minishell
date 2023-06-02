/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:23:18 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/02 17:25:31 by mvogel           ###   ########lyon.fr   */
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
	if (c == ' ' || c == '\t' || c == '\0')
		return (1);
	else
		return (0);
}

int	only_whitespace(char *line)
{
	int	i;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	if (!line[i])
		return (1);
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

void	error_mem(t_data *data)
{
	perror("Memory allocation failed");
	ft_quit(data, 12);
}
