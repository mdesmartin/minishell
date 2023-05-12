/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:21:55 by julien            #+#    #+#             */
/*   Updated: 2023/05/11 16:57:35 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_envptab(t_data *data)
{
	ft_free_envptab(data);
	data->envp_tab = ft_lst_to_tabtab(data, data->envp);
}

void	ft_builtin_slash(t_data *data, char *directory)
{
	if (access(directory, F_OK) == -1)
	{
		ft_putstr3_fd("minishell: ", directory, ": ", 2);
		perror(NULL);
		ft_quit(data, 0);
	}
	else if (access(directory, X_OK) == -1)
	{
		ft_putstr3_fd("minishell: ", directory, ": ", 2);
		perror(NULL);
		ft_quit(data, 0);
	}
	else
	{
		ft_putstr3_fd("minishell: ", directory, ": Is a directory\n", 2);
		ft_quit(data, 126);
	}
}


