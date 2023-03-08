/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:25:34 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/08 16:57:00 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_path(t_data *data, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
(void)data;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "cat"); //cat a remplacer
		if (!tmp)
			perror("Error when adding the cmd to the path");
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		i++;
	}
	ft_free_tab(paths);
	return (tmp);
}

char	*ft_get_arg_path(t_data *data)
{
	int		i;
	char	*tmp;
	char	**paths;

	tmp = getenv("PATH");
	paths = ft_split(tmp, ':');
	if (!paths)
		perror("Error when spliting PATH");
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			perror("Error when adding \'/\' to the path");
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (ft_find_path(data, paths));
}

// static void	ft_is_path_in_cmd(t_data *data)
// {
// 	int		i;

// 	i = 0;
// 	while (i < data->nb_cmd)
// 	{
// 		if (data->cmd_args[i][0] == NULL)
// 			data->cmd_path[i] = NULL;
// 		else if (access(data->cmd_args[i][0], X_OK) == 0)
// 		{
// 			data->cmd_path[i] = ft_strdup(data->cmd_args[i][0]);
// 			if (!data->cmd_path[i])
// 				ft_error(data, "Error when retrieving cmd_path");
// 		}
// 		else if (data->cmd_args[i][0][0] != '.'
// 			&& data->cmd_args[i][0][0] != '/')
// 			ft_find_path(data, i);
// 		else
// 			data->cmd_path[i] = NULL;
// 		i++;
// 	}
// }
