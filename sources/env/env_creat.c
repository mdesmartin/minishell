/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:25:51 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/15 15:18:03 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_creat_variable(t_data *data, char *variable, char *value)
{
	t_envp		*tmp;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		ft_error(data, "Memory allocation failed: envp_init", 12);
	tmp->variable = strdup(variable);
	if (!tmp->variable)
		ft_error(data, "Memory allocation failed: envp_creat", 12);
	tmp->value = strdup(value);
	if (!tmp->value)
		ft_error(data, "Memory allocation failed: envp_creat", 12);
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}

void	ft_creat_envp(t_data *data)
{
	data->envp = ft_calloc(1, sizeof(t_envp));
	if (!data->envp)
		ft_error(data, "Memory allocation failed: envp_creat", 12);
	data->envp->variable = strdup("PWD");
	if (!data->envp->variable)
		ft_error(data, "Memory allocation failed: envp_creat", 12);
	data->envp->value = getcwd(NULL, 0);
	if (!data->envp->value)
		ft_error(data, "Memory allocation failed: envp_creat", 12);
	data->envp->next = NULL;
	ft_creat_variable(data, "SHLVL", "1");
}
