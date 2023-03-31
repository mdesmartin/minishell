/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:25:51 by julien            #+#    #+#             */
/*   Updated: 2023/03/31 15:20:31 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_creat_variable(t_envp *envp, char *variable, char *value)
{
	t_envp		*tmp;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		perror("Memory allocation failed while envp_init!");
	tmp->variable = strdup(variable);
	if (!tmp->variable)
		perror("Memory allocation failed while envp_creat!");
	tmp->value = strdup(value);
	if (!tmp->value)
		perror("Memory allocation failed while envp_creat!");
	tmp->next = NULL;
	ft_envadd_back(&envp, tmp);
}

void	ft_creat_envp(t_data *data)
{
	data->envp = ft_calloc(1, sizeof(t_envp));
	if (!data->envp)
		perror("Memory allocation failed while envp_creat!");
	data->envp->variable = strdup("PWD");
	if (!data->envp->variable)
		perror("Memory allocation failed while envp_creat!");
	data->envp->value = getcwd(NULL, 0);
	if (!data->envp->value)
		perror("Memory allocation failed while envp_creat!");
	data->envp->next = NULL;
	ft_creat_variable(data->envp, "SHLVL", "1");
}
