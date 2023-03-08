/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/08 11:37:30 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//premier arg cmd[0], puis sn


void	create_chain(t_list **cmd, char **pipe)
{
	// int	i;

	// i = 0;
	// while (pipe[i])
	// {
		if (*cmd == NULL)
			*cmd = ft_lstnew((void**)pipe);
		else
			ft_lstadd_back(cmd, ft_lstnew((void**)pipe));
		// i++;
	// }
	free(pipe);
	return ;
}

void	divide_pipes(t_list **cmd, char *input)
{
	char	**input_line;
	char	**pipe;
	int			i;

	input_line = ft_split(input, '|');
	if (!input_line)
		return (free(input), exit(-1));//error msg to add
	free(input);
	i = 0;
	while (input_line[i])
	{
		pipe = ft_split(input_line[i], ' ');
		create_chain(cmd, pipe);
	}
	free_tab(input_line);
	return ;
}



int	parsing(t_list **cmd, char *input)
{
	divide_pipes(cmd, input);

	return (0);
}