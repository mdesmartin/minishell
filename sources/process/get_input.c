/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:18:56 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/11 11:12:36 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_extract_input_file(t_pipeline *pipe, char *str, int i, int k)
{
	int	j;

	pipe->input[k] = ft_strdup("0");
	k++;
	str[i] = ' ';
	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	while (str[j] != ' ')
		j++;
	pipe->input[k] = ft_substr(str, i, j - i);
	k++;
	while (str[i] && i != j)
	{
		str[i] = ' ';
		i++;
	}
	return (i);
}

static int	ft_extract_input_heredoc(t_pipeline *pipe, char *str, int i, int k)
{
	int	j;

	pipe->input[k] = ft_strdup("1");
	k++;
	str[i] = ' ';
	str[i + 1] = ' ';
	while (str[i] && str[i] == ' ')
		i++;
	j = i;
	while (str[j] && str[j] != ' ')
		j++;
	pipe->input[k] = ft_substr(str, i, j - i);
	k++;
	while (str[i] && i != j)
	{
		str[i] = ' ';
		i++;
	}
	return (i);
}

static int	ft_inredic_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] != '<')
			count++;
		i++;
	}
	return (count);
}

void	ft_extract_inputredir(t_pipeline *pipe, char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	pipe->input = ft_calloc(ft_inredic_count(str) * 2 + 1, sizeof(char **));
	if (!pipe->input)
		perror("Error while allocating memory for extract_inputdir !");
	while (str[i])
	{
		if (str[i + 1] && str[i] == '<' && str[i + 1] != '<')
		{
			i = ft_extract_input_file(pipe, str, i, k);
			k += 2;
		}
		else if (str[i + 1] && str[i] == '<' && str[i + 1] == '<')
		{
			i = ft_extract_input_heredoc(pipe, str, i, k);
			k += 2;
		}
		if (str[i])
			i++;
	}
}

