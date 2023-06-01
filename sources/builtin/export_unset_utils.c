/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:33:27 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/01 13:30:40 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_exportopt(t_data *data, char *command1)
{
	if (ft_strncmp("-", command1, 1) == 0)
	{
		ft_dprintf(2, "minishell : export: %c%c: options are not supported\n",
			command1[0], command1[1]);
		data->exit_code = 2;
		return (1);
	}
	return (0);
}

int	ft_check_exportvar(char *variable)
{
	int	i;

	i = 1;
	if (ft_isalpha(variable[0]) == 0 && variable[0] != '_')
	{
		ft_dprintf(2, "minishell : export: `%s': not a valid identifier\n",
			variable);
		return (1);
	}
	while (variable[i] && variable[i] != '=')
	{
		if (variable[i] == '+' && variable[i + 1] == '=')
			break ;
		else if (ft_isalnum(variable[i]) == 0 && variable[i] != '_')
		{
			ft_dprintf(2, "minishell : export: `%s': not a valid identifier\n",
				variable);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_unsetvar(char *variable)
{
	int	i;

	i = 1;
	if (ft_isalpha(variable[0]) == 0 && variable[0] != '_')
	{
		ft_dprintf(2, "minishell : unset: `%s': not a valid identifier\n",
			variable);
		return (1);
	}
	while (variable[i])
	{
		if (ft_isalnum(variable[i]) == 0 && variable[i] != '_')
		{
			ft_dprintf(2, "minishell : unset: `%s': not a valid identifier\n",
				variable);
			return (1);
		}
		i++;
	}
	return (0);
}
