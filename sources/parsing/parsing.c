/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/27 17:16:52 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_tab(char **pipe_tab);

void	create_chain(t_list **cmd, char **pipe)
{
	if (*cmd == NULL)
		*cmd = ft_lstnew((void **)pipe);
	else
		ft_lstadd_back(cmd, ft_lstnew((void **)pipe));
	return ;
}

int	parsing(t_data *data, char *input)
{
	int		nb_p;

	nb_p = nb_pipes(input);
	if (nb_p == -1)
		return (-1);
	// ft_printf("nb_pipes : %d\n", nb_p);
	split_pipes(data, nb_pipes, input);
	// dollar(data);
	return (0);
}

// void	create_chain(t_list **cmd, char **pipe)
// {
// 	if (*cmd == NULL)
// 		*cmd = ft_lstnew((void**)pipe);
// 	else
// 		ft_lstadd_back(cmd, ft_lstnew((void **)pipe));
// 	return ;
// }

// dabbord checker les quotes, puis deplacer le i a la fin des quotes,
// ensuite split au pipe le bloc
// chaque maillon contient un pipe, chqaue str du tab est un token un pipe
// dabbord creer un tab (pipe_tab) avec a chaque str un pipe, le traiter puis
// ensuite a la fin split et put in chain

// void	print_tab(char **pipe_tab)
// {
// 	int i = 0;

// 	while (pipe_tab[i])
// 	{
// 		ft_printf("%s\n", pipe_tab[i]);
// 		i++;
// 	}
// 	return ;
// }

// void	print_chain(t_list *cmd)
// {
// 	t_list *cp;
// 	int	i;

// 	cp = cmd;
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
