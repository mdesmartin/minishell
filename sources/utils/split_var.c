/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:45:33 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/05 13:50:17 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_value(t_data *data, char **res, char *value)
{
	if (ft_strlen(value) == 0)
		res[1] = NULL;
	else
	{
		res[1] = ft_strdup(value);
		if (!res[1])
		{
			ft_free_tab(res);
			ft_error(data, "Memory allocation failed: spliting envp var", 12);
		}
	}
}

char	**ft_split_var(t_data *data, char *var)
{
	char	**res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_calloc(3, sizeof(char *));
	if (!res)
		ft_error(data, "Memory allocation failed: spliting envp var", 12);
	tmp = var;
	while (tmp && *tmp != '=')
	{
		tmp++;
		i++;
	}
	if (*tmp == '=')
		tmp++;
	res[0] = ft_substr(var, 0, i);
	if (!res[0])
		ft_error(data, "Memory allocation failed: spliting envp var", 12);
	ft_get_value(data, res, tmp);
	return (res);
}
