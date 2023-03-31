/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/31 14:39:26 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static char	*ft_find_path(t_data *data, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], s_read_cnt(data->cmd)->command[0]);
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

static char	*ft_is_path_in_cmd(t_data *data)
{
	char	*tmp;

	if (access(s_read_cnt(data->cmd)->command[0], X_OK) == 0)
	{
		tmp = ft_strdup(s_read_cnt(data->cmd)->command[0]);
		if (!tmp)
			ft_error(data, "Error when retrieving cmd_path");
		return (tmp);
	}
	return (NULL);
}

char	*ft_getenv(t_envp *envp, char *variable)
{
	t_envp	*tmp;
	int		n;

	tmp = envp;
	n = ft_strlen(variable) + 1;
	while (tmp)
	{
		if (ft_strncmp(variable, tmp->variable, n) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_get_arg_path(t_data *data)
{
	int		i;
	char	*tmp;
	char	**paths;

	tmp = ft_is_path_in_cmd(data);
	if (tmp)
		return (tmp);
	tmp = ft_getenv(data->envp, "PATH");
	if (!tmp)
		perror("Error when retrieving PATH! ");
	paths = ft_split(tmp, ':');
	if (!paths)
		perror("Error when spliting PATH! ");
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
