/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:02:45 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/08 11:33:35 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static void	free_del(void **content)
{
	free_tab((char**)content);
	content = NULL;
}

void	free_n_exit(t_list **cmd)
{
	ft_lstclear(cmd, free_del);
	free(cmd);
	exit(0);
}

// void	display_error(t_list **cmd)
// {
// 	ft_putstr_fd("Error\n", 2);
// 	free_n_exit(cmd);
// }
