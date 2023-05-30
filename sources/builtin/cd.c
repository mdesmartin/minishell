/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:47:41 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/30 14:47:52 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_update_pwd(t_data *data)
{
	t_envp	*pwd;

	data->pwd = getcwd(NULL, 0);
	if (data->pwd == NULL)
		ft_perror(data, "cd: getcwd() failed", 1);
	pwd = data->envp;
	while (pwd)
	{
		if (ft_strncmp("PWD", pwd->variable, 4) == 0)
			break ;
		pwd = pwd->next;
	}
	if (!pwd)
		return ;
	if (pwd->value)
		free(pwd->value);
	pwd->value = ft_strdup(data->pwd);
	if (!pwd->value)
		ft_error(data, "Memory allocation failed: pwd->value", 12);
}

static void	ft_update_oldpwd(t_data *data)
{
	t_envp	*oldpwd;

	if (data->oldpwd)
		free(data->oldpwd);
	data->oldpwd = data->pwd;
	oldpwd = data->envp;
	while (oldpwd)
	{
		if (ft_strncmp("OLDPWD", oldpwd->variable, 7) == 0)
			break ;
		oldpwd = oldpwd->next;
	}
	if (!oldpwd)
		return ;
	if (oldpwd->value)
		free(oldpwd->value);
	oldpwd->value = ft_strdup(data->oldpwd);
	if (!oldpwd->value)
		ft_error(data, "Memory allocation failed: oldpwd->value", 12);
}

static void	ft_update_cd(t_data *data)
{
	ft_update_oldpwd(data);
	ft_update_pwd(data);
	ft_update_envptab(data);
}

void	ft_builtin_cd(t_data *data, char **command)
{
	data->exit_code = 0;
	if (command[1] != NULL && command[2] != NULL)
	{
		data->exit_code = 1;
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return ;
	}
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
		return ;
	}
	if (data->exit_code == 0)
		ft_update_cd(data);
}
