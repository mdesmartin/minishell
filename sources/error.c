/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:55:30 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/06 16:15:07 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_rfree_tab(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
}

void	ft_quit(t_data *data, int code)
{
	int	i;

	i = -1;
	if (data->pipes != NULL)
	{
		while (++i < data->nb_cmd - 1)
			free(data->pipes[i]);
		free(data->pipes);
		data->pipes = NULL;
	}
	free_lst(&data->cmd);
	free(data->cmd);
	ft_free_envplst(data);
	ft_free_envptab(data);
	exit(code);
}

void	ft_error(t_data *data, char *s)
{
	ft_putstr_fd(s, 2);
	perror(" ");
	ft_quit(data, 1);
}

void	ft_free_envptab(t_data *data)
{
	int	i;

	i = 0;
	if (!data->envp_tab)
		return ;
	while (data->envp_tab[i])
	{
		free(data->envp_tab[i]);
		data->envp_tab[i] = NULL;
		i++;
	}
	free(data->envp_tab);
	data->envp_tab = NULL;
}
