/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:42:18 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/16 11:23:31 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data)
{
	t_envp	*tmp;

	tmp = malloc(sizeof(t_envp));
	if (!tmp)
		perror("Error while allocating memory for envp!");
	tmp->env = ft_strdup(data->cmd->content[1]);
	ft_envadd_back(&data->envp, tmp);
}

void	ft_print_export(t_data *data)
{
	t_envp		*tmp;

	tmp = data->envp;
	while (tmp)
	{
		ft_printf("declare -x ");
		ft_printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
}
