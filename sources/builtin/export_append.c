/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:38:44 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/26 14:04:07 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split_var_app(t_data *data, char *var)
{
	char	**res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_calloc(3, sizeof(char *));
	if (!res)
		ft_error(data, "Memory allocation failed: spliting envp var", 12);
	tmp = var;
	while (tmp && *tmp != '+')
	{
		tmp++;
		i++;
	}
	if (*tmp == '+')
		tmp += 2;
	res[0] = ft_substr(var, 0, i);
	res[1] = ft_strdup(tmp);
	return (res);
}

static void	ft_export_add(t_data *data, char *command)
{
	t_envp	*tmp;
	char	**buffer;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		ft_error(data, "Memory allocation failed: envp", 12);
	buffer = ft_split_var_app(data, command);
	if (!buffer)
		ft_error(data, "Memory allocation failed for export_add!", 12);
	tmp->variable = buffer[0];
	tmp->value = buffer[1];
	free(buffer);
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}

static void	ft_export_mod(t_data *data, t_envp *var, char *command)
{
	char	**buffer;
	char	*new_value;

	buffer = ft_split_var_app(data, command);
	if (!buffer)
		ft_error(data, "Memory allocation failed for export_mod!", 12);
	new_value = ft_strjoin(var->value, buffer[1]);
	if (!new_value)
		ft_error(data, "Memory allocation failed for export_mod!", 12);
	free(var->value);
	var->value = new_value;
	ft_free_tab(buffer);
}

int	ft_export_append(t_data *data, char *variable)
{
	t_envp	*var;
	int		i;

	i = 0;
	while (variable[i])
	{
		if (variable[i] == '+' && variable[i + 1] == '=')
		{
			var = ft_is_var_in_env(data, variable);
			if (var != NULL)
				ft_export_mod(data, var, variable);
			else
				ft_export_add(data, variable);
			return (1);
		}
		i++;
	}
	return (0);
}

