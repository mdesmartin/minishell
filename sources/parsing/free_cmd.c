/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:02:45 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/31 13:50:52 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	free_del(void *content)
{
	free_tab(s_convert_content(content)->command);
	// free_tab(s_convert_content(content)->input);
	// free_tab(s_convert_content(content)->output);
	content = NULL;
}

void	free_lst(t_list **cmd)
{
	ft_lstclear(cmd, free_del);
	return ;
}
