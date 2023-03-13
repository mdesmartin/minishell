/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:42 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/13 11:30:37 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_data_init(t_data *data, char **envp)
{
	data->nb_cmd = 0;
	data->pipes = ft_calloc((data->nb_cmd + 1), sizeof(int *));
	if (!data->pipes)
		perror("ft_calloc failed for data->pipes!\n");
	data->cmd = malloc(sizeof(t_list *));
	if (!data->cmd)
		perror("Error while allocating memory for data->cmd!\n");
	data->cmd = NULL;
	if (!envp[0])
		ft_printf("Error : Environment not found!\n");
	data->envp = envp;
}

void	ft_close_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}
