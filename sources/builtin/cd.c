/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:47:41 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/05 14:10:10 by julien           ###   ########lyon.fr   */
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
					perror("Memory allocation failed for SHLVL's value!");
			}
			return ;
		}
		tmp = tmp->next;
	}
	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		perror("Memory allocation failed while check_oldpwd!");
	tmp->variable = strdup("OLDPWD");
	if (!tmp->variable)
		perror("Memory allocation failed while check_oldpwd!");
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
		perror("Error while calling getcwd()! ");
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

void	ft_builtin_cd(t_data *data)
{
	char	*home;

	ft_check_pwd(data);
	ft_check_oldpwd(data);
	if (s_read_cnt(data->cmd)->command[1] != NULL
		&& s_read_cnt(data->cmd)->command[2] != NULL)
		printf("cd: too many arguments\n");
	if (s_read_cnt(data->cmd)->command[1] == NULL)
	{
		home = ft_get_home(data);
		if (!home)
			return ;
		if (chdir(home) == -1)
			perror("Error while calling chdir()! ");
	}
	else if (ft_strncmp("-", s_read_cnt(data->cmd)->command[1], 2) == 0)
	{
		if (chdir(ft_getenv(data->envp, "OLDPWD")) == -1)
			perror("Error while calling chdir()! ");
	}
	else if (chdir(s_read_cnt(data->cmd)->command[1]) == -1)
		perror("Error while calling chdir()! ");
	ft_update_oldpwd(data);
	ft_update_pwd(data);
	ft_update_envptab(data);
}

// apres cd seul, OLPWD disparait