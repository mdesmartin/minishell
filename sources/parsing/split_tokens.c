/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:25:38 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/15 15:25:55 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_charsetd(char str, char *charset)
{
	while (*charset)
	{
		if (str == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	wordlend(char *str, char *charset)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (str[i])
	{
		if (c == '\0' && (str[i] == '\'' || str[i] == '"'))
			c = str[i];
		else if (c == str[i])
			c = '\0';
		if (c == '\0' && is_charsetd(str[i], charset))
			return (i);
		i++;
	}
	return (i);
}

static int	wordcountd(char *str, char *charset)
{
	int		a;
	char	c;

	a = 0;
	c = '\0';
	while (*str)
	{
		if (c == '\0' && (*str == '\'' || *str == '\"'))
			c = *str;
		else if (c == *str)
			c = '\0';
		if ((is_charsetd(*str, charset) && c == '\0' && *(str + 1) != 0))
		{
			a++;
			while (*str && is_charsetd(*str, charset))
				str++;
			if (!*str)
				return (a);
		}
		else
			str++;
		if (!*str)
			a++;
	}
	return (a);
}

static char	*strduppd(char *src, int j)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc((j + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < j && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**split_tokens(char *str, char *charset)
{
	char		**dest;
	int			size;
	int			j;
	int			i;

	i = -1;
	while (*str && is_charsetd(*str, charset))
		str++;
	size = wordcountd((char *)str, charset);
	dest = calloc((size + 1), sizeof(char *));
	if (!dest)
		return (NULL);
	while (++i < size)
	{
		while (is_charsetd((char)*str, charset))
			str++;
		j = wordlend((char *)str, charset);
		dest[i] = strduppd((char *)str, j);
		if (!dest[i])
			return (free_tab(dest), NULL);
		str += j;
	}
	return (dest);
}
