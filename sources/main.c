/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/08 17:17:26 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_list	**cmd;
	struct sigaction sign;
	char	*input;

	sign.sa_handler = get_signal;

	cmd = malloc(sizeof(t_list *));
	if (!cmd)
		return (ft_putstr_fd("Error\n", 2), exit(0), -1);
	*cmd = NULL;
    while (1)
    {
		sigaction(SIGINT, &sign, NULL);
		sigaction(SIGSEGV, &sign, NULL);
        input = readline("[minishell]> ");
		parsing(cmd, input);
		free_lst(cmd);
    }
	return (0);
}

/// valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell