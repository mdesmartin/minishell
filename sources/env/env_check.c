/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:18:49 by julien            #+#    #+#             */
/*   Updated: 2023/03/30 12:46:16 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_creat_pwd(t_data *data)
{
	t_envp		*tmp;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		perror("Memory allocation failed while creat_pwd!");
	tmp->variable = strdup("PWD");
	if (!tmp->variable)
		perror("Memory allocation failed while creat_pwd!");
	tmp->value = getcwd(NULL, 0);
	if (!tmp->value)
		perror("Memory allocation failed while creat_pwd!");
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}

static void	ft_check_pwd(t_data *data)
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
					perror("Memory allocation failed for SHLVL's value!");
			}
			return ;
		}
		tmp = tmp->next;
	}
	ft_creat_pwd(data);
}

static void	ft_creat_shlvl(t_data *data)
{
	t_envp		*tmp;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		perror("Memory allocation failed while creat_shlvl!");
	tmp->variable = strdup("SHLVL");
	if (!tmp->variable)
		perror("Memory allocation failed while creat_shlvl!");
	tmp->value = strdup("0");
	if (!tmp->value)
		perror("Memory allocation failed while creat_shlvl!");
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}

static void	ft_check_shlvl(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("SHLVL", tmp->variable, 6) == 0)
		{
			if (!tmp->value)
			{
				tmp->value = ft_strdup("0");
				if (!tmp->value)
					perror("Memory allocation failed for SHLVL's value!");
			}
			return ;
		}
		tmp = tmp->next;
	}
	ft_creat_shlvl(data);
}

void	ft_check_envp(t_data *data)
{
	ft_check_shlvl(data);
	ft_check_pwd(data);
}
