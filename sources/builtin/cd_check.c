/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:15:37 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/30 13:29:12 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_creat_pwd(t_data *data)
{
	t_envp		*tmp;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		ft_error(data, "Memory allocation failed: creat_pwd", 12);
	tmp->variable = strdup("PWD");
	if (!tmp->variable)
		ft_error(data, "Memory allocation failed: creat_pwd", 12);
	tmp->value = getcwd(NULL, 0);
	if (!tmp->value)
		ft_perror(data, "creat_pwd: getcwd() failed", 1);
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}

void	ft_check_pwd(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->variable, 4) == 0)
		{
			if (!tmp->value)
			{
				tmp->value = getcwd(NULL, 0);
				if (!tmp->value)
					ft_perror(data, "cd: getcwd() failed", 1);
			}
			return ;
		}
		tmp = tmp->next;
	}
	ft_creat_pwd(data);
}

void	ft_check_oldpwd(t_data *data)
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
					ft_perror(data, "cd: getcwd() failed", 1);
			}
			return ;
		}
		tmp = tmp->next;
	}
	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		ft_error(data, "Memory allocation failed: check_oldpwd", 12);
	tmp->variable = strdup("OLDPWD");
	if (!tmp->variable)
		ft_error(data, "Memory allocation failed: check_oldpwd", 12);
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}
