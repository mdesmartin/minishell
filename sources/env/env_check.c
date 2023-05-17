/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 12:18:49 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/17 16:08:20 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_creat_shlvl(t_data *data)
{
	t_envp		*tmp;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		ft_error(data, "Memory allocation failed: creat_shlvl", 12);
	tmp->variable = strdup("SHLVL");
	if (!tmp->variable)
		ft_error(data, "Memory allocation failed: creat_shlvl", 12);
	tmp->value = strdup("0");
	if (!tmp->value)
		ft_error(data, "Memory allocation failed: creat_shlvl", 12);
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
					ft_error(data,
						"Memory allocation failed: SHLVL's value", 12);
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
