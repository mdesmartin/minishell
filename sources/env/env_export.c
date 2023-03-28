/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:42:18 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/28 15:29:16 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export_add(t_data *data)
{
	t_envp	*tmp;
	char	**buffer;

	tmp = malloc(sizeof(t_envp));
	if (!tmp)
		perror("Error while allocating memory for envp!");
	buffer = ft_split_var(data->cmd->content[1]);
	if (!buffer)
		ft_error(data, "Malloc failed for export_add!");
	tmp->variable = buffer[0];
	tmp->value = buffer[1];
	tmp->next = NULL;
	free(buffer);
	ft_envadd_back(&data->envp, tmp);
}

static int	ft_varlen(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static t_envp	*ft_is_var_in_env(t_data *data)
{
	t_envp				*tmp;
	long unsigned int	n;

	tmp = data->envp;
	n = ft_varlen(data->cmd->content[1]);
	while (tmp)
	{
		if (ft_strncmp(data->cmd->content[1], tmp->variable, n) == 0
			&& ft_strlen(tmp->variable) == n)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	ft_export_mod(t_data *data, t_envp *var)
{
	char	**buffer;

	buffer = ft_split_var(data->cmd->content[1]);
	if (!buffer)
		ft_error(data, "Malloc failed for export_mod!");
	free(var->value);
	var->value = buffer[1];
	free(buffer[0]);
	free(buffer);
}

void	ft_export(t_data *data)
{
	t_envp	*var;

	var = ft_is_var_in_env(data);
	if (var != NULL)
		ft_export_mod(data, var);
	else
		ft_export_add(data);
	ft_free_envptab(data);
	data->envp_tab = ft_lst_to_tabtab(data->envp);
}
