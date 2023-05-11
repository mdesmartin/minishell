/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:33:27 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/11 17:24:58 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_exportopt(t_data *data, char *command1)
{
	if (ft_strncmp("-", command1, 1) == 0)
	{
		ft_putstr_fd("minishell : export: `", 2);
		ft_putchar_fd(command1[0], 2);
		ft_putchar_fd(command1[1], 2);
		ft_putstr_fd("': options are not supported\n", 2);
		data->exit_code = 1;
		return (1);
	}
	return (0);
}

int	ft_check_exportvar(char *variable)
{
	int	i;

	i = 1;
	if (variable[0] == '='
		|| (ft_isalpha(variable[0]) == 0 && variable[0] != '_'))
	{
		ft_putstr3_fd("minishell : export: `", variable,
			"': not a valid identifier\n", 2);
		return (1);
	}
	while (variable[i] && variable[i] != '=')
	{
		if (ft_isalnum(variable[i]) == 0 && variable[i] != '_')
		{
			ft_putstr3_fd("minishell : export: `", variable,
				"': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_unsetvar(char *variable)
{
	int	i;
	int	end;

	i = 1;
	end = ft_strlen(variable) - 1;
	if (variable[0] == '=' || variable[end] == '='
		|| (ft_isalpha(variable[0]) == 0 && variable[0] != '_'))
	{
		ft_putstr3_fd("minishell : unset: `", variable,
			"': not a valid identifier\n", 2);
		return (1);
	}
	while (variable[i] && variable[i] != '=')
	{
		if (ft_isalnum(variable[i]) == 0 && variable[i] != '_')
		{
			ft_putstr3_fd("minishell : unset: `", variable,
				"': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
