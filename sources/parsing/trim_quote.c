/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:37:59 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/01 20:34:44 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	quote_handler(char *dequoted, char *dest, int *i, char quote)
{
	int	first;
	int second;

	first = *i;
	(*i)++;
	while (dest[*i] != quote)
		(*i)++;
	second = *i;
	printf("first:%d\nsecond:%d\n", first, second);
	ft_memcpy(dequoted, dest, first);
	ft_memcpy(&dequoted[first], &dest[first + 1], second - first - 1);
	ft_memcpy(&dequoted[second - 1], &dest[second + 1], ft_strlen(&dest[second]));
	return ;
}

static void	quote_type(char *dequoted, char *dest, int *i)
{
	char quote;

	quote = dest[*i];
	quote_handler(dequoted, dest, i, quote);
	return ;
}

char	*trim_quote(char *dest)
{
	int i;
	int flag;
	char *dequoted;

	i = 0;
	flag = 0;
	dequoted = ft_calloc(ft_strlen(dest), sizeof(char));
	while (dest[i])
	{
		if (dest[i] == '\'' || dest[i] == '\"')
		{
			quote_type(dequoted, dest, &i);
			flag = 1;
		}
		i++;
	}
	if (flag == 1)
		return (free(dest), dequoted);
	else
		return (free (dequoted), dest);
}
