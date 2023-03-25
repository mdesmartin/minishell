/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_4_ju.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/25 13:55:19 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//premier arg cmd[0], puis sn


void	create_chain(t_list **cmd, char **pipe)
{
	if (*cmd == NULL)
		*cmd = ft_lstnew((void**)pipe);
	else
		ft_lstadd_back(cmd, ft_lstnew((void **)pipe));
	return ;
}

void	divide_pipes(t_list **cmd, char *input)
{
	char	**input_pipe;
	char	**pipe;
	int		i;

	input_pipe = ft_split(input, '|');
	if (!input_pipe)
		return (ft_putstr_fd("Error\n", 2), free(input), exit(-1));
	free(input);
	i = 0;
	while (input_pipe[i])
	{
		pipe = ft_split(input_pipe[i], ' ');
		if (!pipe)
			return (perror("Error\n"), free(input));
		create_chain(cmd, pipe);
		i++;
	}
	free_tab(input_pipe);
	return ;
}

// void	print_tab(t_list *cmd)
// {
// 	t_list *cp;
// 	int	i;

// 	cp = *cmd;
// 	ft_putstr_fd("the command is : ", 1);
// 	while (cp)
// 	{
// 		i = 0;
// 		while (cp->content[i])
// 		{
// 			ft_printf("%s", cp->content[i]);
// 			ft_putstr_fd(" ", 1);
// 			i++;
// 		}
// 		ft_putstr_fd("| ", 1);
// 		cp = cp->next;
// 	}
// 	ft_putstr_fd("\n", 1);
// 	return ;
// }

int	parsing(t_data *data, char *input)
{
	divide_pipes(&data->cmd, input);
	// print_tab(cmd);

	return (0);
}
