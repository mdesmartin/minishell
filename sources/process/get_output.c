/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:18:56 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/19 13:52:42 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_extract_output(char **cmd, char **output)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if ((cmd[i][0] == -62 && ft_strlen(cmd[i]) == 1)
			|| (cmd[i][0] == -62 && cmd[i][1] == -62 && ft_strlen(cmd[i]) == 2))
		{
			if (ft_strlen(cmd[i]) == 1)
				output[j] = ft_strdup("0");
			else
				output[j] = ft_strdup("1");
			if (!output[j])
				return (ft_rfree_tab(output, j), 1);
			output[j + 1] = ft_strdup(cmd[i + 1]);
			if (!output[j + 1])
				return (ft_rfree_tab(output, j + 1), 1);
			i++;
			j += 2;
		}
		i++;
	}
	return (0);
}

int	ft_outredic_count(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (tab[i][0] == -62 && ft_strlen(tab[i]) == 1)
			count++;
		else if (tab[i][0] == -62 && tab[i][1] == -62 && ft_strlen(tab[i]) == 2)
			count++;
		i++;
	}
	return (count);
}

char	**ft_extract_outputredir(t_data *data, char **cmd,
	char **pipe_tab, char **input)
{
	char	**output;

	output = ft_calloc(ft_outredic_count(cmd) * 2 + 1, sizeof(char **));
	if (!output || ft_extract_output(cmd, output) != 0)
	{
		free_tab(input);
		free_tab(cmd);
		free_tab(pipe_tab);
		ft_error(data, "Memory allocation failed: ft_extract_output_file", 12);
	}
	ft_del_output(cmd);
	return (output);
}
