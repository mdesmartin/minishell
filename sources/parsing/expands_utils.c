/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:59:47 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/01 18:05:10 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_from_to(char *pipes_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		i;

	i = 0;
	new_size = ft_strlen(pipes_tab) - (end - *start);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	if (!new_content)
	{
		free(pipes_tab);
		return (NULL);
	}
	while (i < *start - 1)
	{
		new_content[i] = pipes_tab[i];
		i++;
	}
	while (pipes_tab[end])
		new_content[i++] = pipes_tab[end++];
	*start = 0;
	free(pipes_tab);
	return (new_content);
}

char	*trim_by_exitcode(char *value, char *pipes_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		old_size;
	int		i;
	int		j;

	if (!value)
		return (free(pipes_tab), NULL);
	i = -1;
	j = 0;
	old_size = end - *start;
	new_size = ft_strlen(pipes_tab) - old_size + ft_strlen(value);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	if (!new_content)
		return (free(value), free(pipes_tab), NULL);
	while (++i < *start - 1)
		new_content[i] = pipes_tab[i];
	while (value[j])
		new_content[i++] = value[j++];
	end++;
	while (pipes_tab[end])
		new_content[i++] = pipes_tab[end++];
	*start = 0;
	return (free(value), free(pipes_tab), new_content);
}

char	*trim_by(char *value, char *pipes_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		old_size;
	int		i;
	int		j;

	if (!value)
		return (free(pipes_tab), NULL);
	i = -1;
	j = 0;
	old_size = end - *start;
	new_size = ft_strlen(pipes_tab) - old_size + ft_strlen(value);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	(void) new_size;
	if (!new_content)
		return (free(pipes_tab), NULL);
	while (++i < *start - 1)
		new_content[i] = pipes_tab[i];
	while (value[j])
		new_content[i++] = value[j++];
	*start = i - 1;
	while (pipes_tab[end])
		new_content[i++] = pipes_tab[end++];
	free(pipes_tab);
	return (new_content);
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
