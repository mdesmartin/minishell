/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:55:30 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/12 14:48:32 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	rl_clear_history();
	exit(code);
}

void	ft_error(t_data *data, char *str)
{
	perror(str);
	ft_quit(data, 1);
}

void	ft_perror(t_data *data, char *str, int code)
{
	perror(str);
	data->exit_code = code;
}
