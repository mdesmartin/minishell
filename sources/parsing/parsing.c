/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/29 16:53:12 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_chain(t_list **cmd, void *content)
{
	if (*cmd == NULL)
		*cmd = ft_lstnew(content);
	else
		ft_lstadd_back(cmd, ft_lstnew(content));
	return ;
}

void	print_chain(t_data *data)
{
	t_list *cp;
	// int	i;

	cp = data->cmd;
	ft_printf("the command is : ");
	while (cp)
	{
		// i = 0;
		// while (s_access_content(cp)->command[0])
		// {
		ft_printf("%s ", s_access_content(cp)->command[0]);
		// i++;
		// }
		ft_printf("| ");
		cp = cp->next; 
	}
	ft_printf("\n");
	return ;
}

int	parsing(t_data *data, char *input)
{
	int		nb_p;

	nb_p = nb_pipes(input);
	if (nb_p == -1)
		return (-1);
	// ft_printf("nb_pipes : %d\n", nb_p);
	split_pipes(data, nb_p, input);
	print_chain(data);
	// dollar(data);
	return (0);
}


// valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell

















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

