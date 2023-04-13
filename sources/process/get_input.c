/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:18:56 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/13 12:25:54 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free_two_line(char **tab, int i)
{
	free(tab[i]);
	free(tab[i + 1]);
	while (tab[i + 2])
	{
		tab[i] = tab[i + 2];
		tab[i + 1] = tab[i + 3];
		i += 2;
	}
	tab[i] = NULL;
	tab[i + 1] = NULL;
}

static void	ft_del_input(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '<' && ft_strlen(cmd[i]) == 1)
		{
			ft_free_two_line(cmd, i);
			i = -1;
		}
		else if (cmd[i][0] == '<' && cmd[i][1] == '<' && ft_strlen(cmd[i]) == 2)
		{
			ft_free_two_line(cmd, i);
			i = -1;
		}
		i++;
	}
}

static void	ft_extract_input(char **cmd, char **input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '<' && ft_strlen(cmd[i]) == 1)
		{
			input[j] = ft_strdup("0");
			input[j + 1] = ft_strdup(cmd[i + 1]);
			i++;
			j += 2;
		}
		else if (cmd[i][0] == '<' && cmd[i][1] == '<' && ft_strlen(cmd[i]) == 2)
		{
			input[j] = ft_strdup("1");
			input[j + 1] = ft_strdup(cmd[i + 1]);
			i++;
			j += 2;
		}
		i++;
	}
}

int	ft_inredic_count(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (tab[i][0] == '<' && ft_strlen(tab[i]) == 1)
			count++;
		else if (tab[i][0] == '<' && tab[i][1] == '<' && ft_strlen(tab[i]) == 2)
			count++;
		i++;
	}
	return (count);
}

void	ft_extract_inputredir(t_data *data, t_pipeline *pipe)
{
	pipe->input = ft_calloc(ft_inredic_count(pipe->command) * 2 + 1,
			sizeof(char **));
	if (!pipe->input)
	{
		ft_perror(data, "Memory allocation failed: ft_extract_input_file", 12);
		ft_quit(data, 1);
	}
	ft_extract_input(pipe->command, pipe->input);
	ft_del_input(pipe->command);
}

