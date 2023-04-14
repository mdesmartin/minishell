/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:47:41 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/12 17:46:06 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_oldpwd(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("OLDPWD", tmp->variable, 4) == 0)
		{
			if (!tmp->value)
			{
				tmp->value = getcwd(NULL, 0);
				if (!tmp->value)
					ft_perror(data, "Memory allocation failed: SHLVL's value ", 12);
			}
			return ;
		}
		tmp = tmp->next;
	}
	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		ft_perror(data, "Memory allocation failed: check_oldpwd", 12);
	tmp->variable = strdup("OLDPWD");
	if (!tmp->variable)
		ft_perror(data, "Memory allocation failed: check_oldpwd", 12);
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}

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
	return (NULL);
}

static void	ft_update_pwd(t_data *data)
{
	t_envp	*pwd;
	char	*buffer;

	pwd = data->envp;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		ft_perror(data, "getcwd() failed", 1);
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

void	ft_builtin_cd(t_data *data, char **command)
{
	char	*home;

	ft_check_pwd(data);
	ft_check_oldpwd(data);
	if (command[1] != NULL && command[2] != NULL)
		printf("cd: too many arguments\n");
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

// apres cd seul, OLPWD disparait