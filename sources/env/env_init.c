/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:05:59 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/30 15:26:18 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_envp_init(t_data *data)
{
	extern char	**environ;
	char		**buffer;

	data->envp = ft_calloc(1, sizeof(t_envp));
	if (!data->envp)
		perror("Memory allocation failed while envp_init!");
	buffer = ft_split_var(environ[0]);
	data->envp->variable = buffer[0];
	data->envp->value = buffer[1];
	data->envp->next = NULL;
	free(buffer);
}

static void	ft_cp_envp(t_data *data)
{
	extern char	**environ;
	t_envp		*tmp;
	char		**buffer;
	int			i;

	i = 1;
	ft_envp_init(data);
	while (environ[i])
	{
		tmp = ft_calloc(1, sizeof(t_envp));
		if (!tmp)
			perror("Memory allocation failed while envp_init!");
		buffer = ft_split_var(environ[i]);
		tmp->variable = buffer[0];
		tmp->value = buffer[1];
		tmp->next = NULL;
		free(buffer);
		ft_envadd_back(&data->envp, tmp);
		i++;
	}
}

static void	ft_update_envp(t_data *data)
{
	t_envp	*tmp;
	int		shlvl;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("SHLVL", tmp->variable, 6) == 0)
		{
			shlvl = ft_atoi(tmp->value);
			free(tmp->value);
			shlvl++;
			tmp->value = ft_itoa(shlvl);
			if (!tmp->value)
				perror("Memory allocation failed while updating SHLVL!");
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_envp(t_data *data)
{
	extern char	**environ;

	if (!environ[0])
		ft_creat_envp(data);
	else
	{
		ft_cp_envp(data);
		ft_check_envp(data);
		ft_update_envp(data);
	}
}
