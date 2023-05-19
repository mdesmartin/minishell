/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:18:56 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/19 13:52:42 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_extract_input(char **cmd, char **input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if ((cmd[i][0] == -60 && ft_strlen(cmd[i]) == 1)
			|| (cmd[i][0] == -60 && cmd[i][1] == -60 && ft_strlen(cmd[i]) == 2))
		{
			if (ft_strlen(cmd[i]) == 1)
				input[j] = ft_strdup("0");
			else
				input[j] = ft_strdup("1");
			if (!input[j])
				return (ft_rfree_tab(input, j), 1);
			input[j + 1] = ft_strdup(cmd[i + 1]);
			if (!input[j + 1])
				return (ft_rfree_tab(input, j + 1), 1);
			i++;
			j += 2;
		}
		i++;
	}
	return (0);
}

int	ft_inredic_count(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (tab[i][0] == -60 && ft_strlen(tab[i]) == 1)
			count++;
		else if (tab[i][0] == -60 && tab[i][1] == -60 && ft_strlen(tab[i]) == 2)
			count++;
		i++;
	}
	return (count);
}

char	**ft_extract_inputredir(t_data *data, char **cmd, char **pipe_tab)
{
	char	**input;

	input = ft_calloc(ft_inredic_count(cmd) * 2 + 1, sizeof(char **));
	if (!input || ft_extract_input(cmd, input) != 0)
	{
		free_tab(cmd);
		free_tab(pipe_tab);
		ft_error(data, "Memory allocation failed: ft_extract_input_file", 12);
	}
	ft_del_input(cmd);
	return (input);
}
