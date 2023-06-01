/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:55:30 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/01 15:31:53 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_free(void *data)
{
	if (data)
	{
		free(data);
		data = NULL;
	}
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
	ft_close_hd_fds(data);
	free_lst(&data->cmd);
	ft_free(data->cmd);
	ft_free(data->pwd);
	ft_free(data->oldpwd);
	ft_free_envplst(data);
	ft_free_envptab(data);
	rl_clear_history();
	exit(code);
}

void	ft_error(t_data *data, char *str, int code)
{
	perror(str);
	ft_quit(data, code);
}

void	ft_perror(t_data *data, char *str, int code)
{
	perror(str);
	data->exit_code = code;
}
