/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:37:20 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/11 16:22:10 by jmoutous         ###   ########lyon.fr   */
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
			ft_error(data, "Error when adding the cmd to the path");
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		i++;
	}
	ft_free_tab(paths);
	return (tmp);
}

static char	*ft_is_path_in_cmd(t_data *data, char **command)
{
	char	*tmp;

	if (access(command[0], X_OK) == 0)
	{
		tmp = ft_strdup(command[0]);
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

static void	ft_add_bslash(t_data *data, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			ft_perror(data, "Error when adding \'/\' to the path", 12);
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
		ft_putstr_fd("minishell: ", 2);
		perror(command[0]);
		ft_quit(data, 127);
	}
	paths = ft_split(tmp, ':');
	if (!paths)
		ft_perror(data, "Error when spliting PATH!", 1);
	ft_add_bslash(data, paths);
	return (ft_find_path(data, command, paths));
}
