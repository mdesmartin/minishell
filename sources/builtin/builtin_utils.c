/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:21:55 by julien            #+#    #+#             */
/*   Updated: 2023/05/15 16:38:10 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_envptab(t_data *data)
{
	ft_free_envptab(data);
	data->envp_tab = ft_lst_to_tabtab(data, data->envp);
}

int	ft_is_directory(char *directory)
{
	int	dirend;

	dirend = ft_strlen(directory) - 1;
	if (directory[0] == '/' || (directory[0] == '.' && directory[1] == '/')
		|| directory[dirend] == '/')
		return (1);
	return (0);
}

void	ft_builtin_slash(t_data *data, char *directory)
{
	if (access(directory, F_OK) == -1)
	{
		ft_dprintf(2, "minishell: %s: ", directory);
		perror(NULL);
		ft_quit(data, 127);
	}
	else if (access(directory, X_OK) == -1)
	{
		ft_dprintf(2, "minishell: %s: ", directory);
		perror(NULL);
		ft_quit(data, 126);
	}
	else
	{
		ft_dprintf(2, "minishell: %s: Is a directory\n", directory);
		ft_quit(data, 126);
	}
}
