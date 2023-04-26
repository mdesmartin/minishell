/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:09:45 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/26 14:11:13 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_rfree_tab(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
}

void	ft_free_envptab(t_data *data)
{
	int	i;

	i = 0;
	if (!data->envp_tab)
		return ;
	while (data->envp_tab[i])
	{
		free(data->envp_tab[i]);
		data->envp_tab[i] = NULL;
		i++;
	}
	free(data->envp_tab);
	data->envp_tab = NULL;
}
