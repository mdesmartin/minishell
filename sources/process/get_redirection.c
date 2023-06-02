/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:42:33 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/02 15:25:45 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_extract_input(char **cmd, char **redirections, int i, int j)
{
	if (ft_strlen(cmd[i]) == 1)
		redirections[j] = ft_strdup("0");
	else
		redirections[j] = ft_strdup("1");
	if (!redirections[j])
	{
		ft_rfree_tab(redirections, j);
		return (-1);
	}
	redirections[j + 1] = ft_strdup(cmd[i + 1]);
	if (!redirections[j + 1])
	{
		ft_rfree_tab(redirections, j + 1);
		return (-1);
	}
	return (0);
}

static int	ft_extract_output(char **cmd, char **redirections, int i, int j)
{
	if (ft_strlen(cmd[i]) == 1)
		redirections[j] = ft_strdup("2");
	else
		redirections[j] = ft_strdup("3");
	if (!redirections[j])
	{
		ft_rfree_tab(redirections, j);
		return (-1);
	}
	redirections[j + 1] = ft_strdup(cmd[i + 1]);
	if (!redirections[j + 1])
	{
		ft_rfree_tab(redirections, j + 1);
		return (-1);
	}
	return (0);
}

static int	ft_get_redirections(char **cmd, char **redirections)
{
	int	i;
	int	j;
	int	return_val;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		return_val = 1;
		if ((cmd[i][0] == -60 && ft_strlen(cmd[i]) == 1)
			|| (cmd[i][0] == -60 && cmd[i][1] == -60 && ft_strlen(cmd[i]) == 2))
			return_val = ft_extract_input(cmd, redirections, i, j);
		else if ((cmd[i][0] == -62 && ft_strlen(cmd[i]) == 1)
			|| (cmd[i][0] == -62 && cmd[i][1] == -62 && ft_strlen(cmd[i]) == 2))
			return_val = ft_extract_output(cmd, redirections, i, j);
		if (return_val == -1)
			return (-1);
		if (return_val == 0)
		{
			j += 2;
			i++;
		}
		i++;
	}
	return (0);
}

static int	ft_redir_count(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if ((tab[i][0] == -60 && ft_strlen(tab[i]) == 1)
			|| (tab[i][0] == -60 && tab[i][1] == -60 && ft_strlen(tab[i]) == 2))
			count++;
		else if ((tab[i][0] == -62 && ft_strlen(tab[i]) == 1)
			|| (tab[i][0] == -62 && tab[i][1] == -62 && ft_strlen(tab[i]) == 2))
			count++;
		i++;
	}
	return (count);
}

char	**ft_extract_redirections(t_data *data, char **cmd, char **pipes_tab)
{
	char	**redirections;
	int		nb_redir;

	nb_redir = ft_redir_count(cmd);
	redirections = ft_calloc(nb_redir * 2 + 1, sizeof(char **));
	if (!redirections || ft_get_redirections(cmd, redirections) != 0)
	{
		free_tab(cmd);
		free_tab(pipes_tab);
		ft_error(data, "Memory allocation failed: ft_extract_redirection", 12);
	}
	ft_del_redirections(cmd);
	return (redirections);
}
