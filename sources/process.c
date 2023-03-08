/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:50 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/08 12:48:51 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process(t_data *data)
{
	int	i;
	int	pids;

	i = -1;
	while (++i < data->nb_cmd - 1)
	{
		data->pipes[i] = malloc(2 * sizeof(int));
		if (!data->pipes[i])
			ft_error(data, "Malloc failed for data->pipes[i]");
		if (pipe(data->pipes[i]) == -1)
			ft_error(data, "Pipe failed for data->pipes[i]");
	}
	i = -1;
	while (++i < data->nb_cmd)
	{
		pids = fork();
		if (pids == -1)
			ft_error(data, "Fork failed");
		if (pids == 0)
			ft_child(data, data->pipes, i);
	}
	ft_close_fds(data);
	while (--i >= 0)
		wait(NULL);
}
