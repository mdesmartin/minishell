/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:59:47 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/17 15:10:46 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//trim a str of a str
char	*trim_from_to(char *pipe_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		i;

	i = 0;
	new_size = ft_strlen(pipe_tab) - (end - *start);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	if (!new_content)
		return (NULL);
	while (i < *start - 1)
	{
		new_content[i] = pipe_tab[i];
		i++;
	}
	while (pipe_tab[end])
		new_content[i++] = pipe_tab[end++];
	*start = 0;
	free(pipe_tab);
	return (new_content);
}

char	*trim_by_exitcode(char *value, char *pipe_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		old_size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	old_size = end - *start;
	new_size = ft_strlen(pipe_tab) - old_size + ft_strlen(value);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	if (!new_content)
		return (NULL);
	while (i < *start - 1)
	{
		new_content[i] = pipe_tab[i];
		i++;
	}
	while (value[j])
		new_content[i++] = value[j++];
	end++;
	while (pipe_tab[end])
		new_content[i++] = pipe_tab[end++];
	*start = 0;
	return (free(value), free(pipe_tab), new_content);
}

char	*trim_by(char *value, char *pipe_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		old_size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	old_size = end - *start;
	new_size = ft_strlen(pipe_tab) - old_size + ft_strlen(value);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	if (!new_content)
		return (NULL);
	while (i < *start - 1)
	{
		new_content[i] = pipe_tab[i];
		i++;
	}
	while (value[j])
		new_content[i++] = value[j++];
	*start = i - 1;
	while (pipe_tab[end])
		new_content[i++] = pipe_tab[end++];
	free(pipe_tab);
	return (new_content);
}
