/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:03:17 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/10 14:10:57 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	ft_free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->pipes != NULL)
	{
		while (++i < data->nb_cmd - 1)
			free(data->pipes[i]);
		free(data->pipes);
	}
}

void	ft_quit(t_data *data)
{
	ft_free_data(data);
}

void	ft_error(t_data *data, char *s)
{
	ft_putstr_fd("\nError\n", 2);
	if (s)
		ft_putstr_fd(s, 2);
	perror(" ");
	ft_putstr_fd("\n", 2);
	ft_quit(data);
	exit (1);
}
