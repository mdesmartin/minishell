/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:47:41 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/09 17:17:20 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_home(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->variable, 5) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	ft_putstr_fd("cd : HOME not set!\n", 2);
	data->exit_code = 1;
	return (NULL);
}

static void	ft_update_pwd(t_data *data)
{
	t_envp	*pwd;
	char	*buffer;

	pwd = data->envp;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		ft_perror(data, "cd: getcwd() failed", 1);
	while (pwd)
	{
		if (ft_strncmp("PWD", pwd->variable, 4) == 0)
			break ;
		pwd = pwd->next;
	}
	pwd->value = buffer;
}

static void	ft_update_oldpwd(t_data *data)
{
	t_envp	*pwd;
	t_envp	*oldpwd;

	pwd = data->envp;
	oldpwd = data->envp;
	while (pwd)
	{
		if (ft_strncmp("PWD", pwd->variable, 4) == 0)
			break ;
		pwd = pwd->next;
	}
	while (oldpwd)
	{
		if (ft_strncmp("OLDPWD", oldpwd->variable, 7) == 0)
			break ;
		oldpwd = oldpwd->next;
	}
	if (oldpwd->value)
		free(oldpwd->value);
	oldpwd->value = pwd->value;
}

static void	ft_check_cd(t_data *data, char **command)
{
	data->exit_code = 0;
	ft_check_pwd(data);
	ft_check_oldpwd(data);
	if (command[1] != NULL && command[2] != NULL)
	{
		data->exit_code = 1;
		printf("cd: too many arguments\n");
	}

}

void	ft_builtin_cd(t_data *data, char **command)
{
	char	*home;

	ft_check_cd(data, command);
	if (data->exit_code != 0)
		return ;
	if (command[1] == NULL)
	{
		home = ft_get_home(data);
		if (!home)
			return ;
		if (chdir(home) == -1)
			ft_perror(data, "chdir() failed", 1);
	}
	else if (ft_strncmp("-", command[1], 2) == 0)
	{
		if (chdir(ft_getenv(data->envp, "OLDPWD")) == -1)
			ft_perror(data, "chdir() failed", 1);
	}
	else if (chdir(command[1]) == -1)
		ft_perror(data, "chdir() failed", 1);
	ft_update_oldpwd(data);
	ft_update_pwd(data);
	ft_update_envptab(data);
}
