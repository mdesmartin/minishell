/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:47:41 by julien            #+#    #+#             */
/*   Updated: 2023/03/29 16:51:55 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_home(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("USER_ZDOTDIR", tmp->variable, 13) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp->value);
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
	free(oldpwd->value);
	oldpwd->value = pwd->value;
}

void	ft_builtin_cd(t_data *data)
{
	if (data->cmd->content[1] != NULL && data->cmd->content[2] != NULL)
		printf("cd: too many arguments\n");
	if (data->cmd->content[1] == NULL)
	{
		if (chdir(ft_get_home(data)) == -1)
			perror("Error while calling chdir()! ");
	}
	else if (chdir(data->cmd->content[1]) == -1)
		perror("Error while calling chdir()! ");
	ft_update_oldpwd(data);
	ft_update_pwd(data);
	ft_free_envptab(data);
	data->envp_tab = ft_lst_to_tabtab(data->envp);
}
