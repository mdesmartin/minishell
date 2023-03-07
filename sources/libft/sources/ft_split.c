/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:23:13 by jmoutous          #+#    #+#             */
/*   Updated: 2022/11/22 08:41:08 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] == c)
		i++;
	if (s[i] == 0)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != '\0')
				count++;
		}
		else
			i++;
	}
	return (count);
}

static void	ft_free_tab(char **tab, int index)
{
	while (index >= 0)
	{
		free(tab[index]);
		index--;
	}
	free(tab);
}

static int	ft_word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	int		word_count;
	char	**tab;

	index = 0;
	word_count = ft_word_count(s, c);
	tab = malloc (sizeof(char *) * (word_count + 1));
	if (tab == NULL)
		return (NULL);
	while (*s != 0 && index < word_count)
	{
		while (*s == c)
			s++;
		tab[index] = ft_substr(s, 0, ft_word_len(s, c));
		if (!tab[index])
		{
			ft_free_tab(tab, index - 1);
			return (NULL);
		}
		s = s + ft_word_len(s, c);
		index++;
	}
	tab[index] = NULL;
	return (tab);
}
