/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:47:41 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/25 18:19:05 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ft_dprintf(2, "minishell: cd: too many arguments\n");
	}
}

void	ft_builtin_cd(t_data *data, char **command)
{
	ft_check_cd(data, command);
	if (data->exit_code != 0)
		return ;
	if (command[1] == NULL || ft_strncmp("~", command[1], 2) == 0
		|| ft_strncmp("~/", command[1], 3) == 0)
		ft_cd_home(data);
	else if (ft_strncmp("-", command[1], 2) == 0)
		ft_cd_back(data);
	else if (command[1][0] == '-' && command[1][1])
		ft_cd_opt(data, command[1]);
	else if (chdir(command[1]) == -1)
	{
		data->exit_code = 1;
		ft_dprintf(2, "minishell: cd: %s: ", command[1]);
		perror(NULL);
	}
	ft_update_oldpwd(data);
	ft_update_pwd(data);
	ft_update_envptab(data);
}
