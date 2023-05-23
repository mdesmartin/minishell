/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:59:47 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/23 10:44:34 by mvogel           ###   ########lyon.fr   */
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
		return (NULL);
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

	i = 0;
	j = 0;
	old_size = end - *start;
	new_size = ft_strlen(pipes_tab) - old_size + ft_strlen(value);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	if (!new_content)
		return (NULL);
	while (i < *start - 1)
	{
		new_content[i] = pipes_tab[i];
		i++;
	}
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

	i = 0;
	j = 0;
	old_size = end - *start;
	new_size = ft_strlen(pipes_tab) - old_size + ft_strlen(value);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	if (!new_content)
		return (NULL);
	while (i < *start - 1)
	{
		new_content[i] = pipes_tab[i];
		i++;
	}
	while (value[j])
		new_content[i++] = value[j++];
	*start = i - 1;
	while (pipes_tab[end])
		new_content[i++] = pipes_tab[end++];
	free(pipes_tab);
	return (new_content);
}
