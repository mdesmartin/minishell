/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:37:20 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/05 14:02:54 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_find_path(t_data *data, char **command, char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], command[0]);
		if (!tmp)
			ft_error(data, "Error when adding the cmd to the path", 12);
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		tmp = NULL;
		i++;
	}
	ft_free_tab(paths);
	return (tmp);
}

static char	*ft_is_path_in_cmd(t_data *data, char **cmd)
{
	char	*tmp;

	if (cmd[0][0] == '.' || cmd[0][0] == '/')
	{
		tmp = ft_strdup(cmd[0]);
		if (!tmp)
			ft_error(data, "Error when retrieving cmd_path", 12);
		return (tmp);
	}
	return (NULL);
}

static void	ft_add_bslash(t_data *data, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			ft_error(data, "Error when adding \'/\' to the path", 12);
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
}

char	*ft_get_arg_path(t_data *data, char **command)
{
	char	*tmp;
	char	**paths;

	tmp = ft_is_path_in_cmd(data, command);
	if (tmp)
		return (tmp);
	tmp = ft_getenv(data->envp, "PATH");
	if (!tmp)
	{
		if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
			ft_error(data, "Error while duplicating file descriptor", 1);
		printf("minishell: %s: command not found\n", command[0]);
		ft_quit(data, 127);
	}
	paths = ft_split(tmp, ':');
	if (!paths)
		ft_error(data, "Error when spliting PATH!", 12);
	ft_add_bslash(data, paths);
	return (ft_find_path(data, command, paths));
}
