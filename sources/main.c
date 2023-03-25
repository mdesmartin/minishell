/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/25 13:41:31 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	struct sigaction	sign;
	static char			*input;
	t_data				data;

	sign.sa_handler = get_signal;
	sigemptyset(&sign.sa_mask);
	sign.sa_flags = SA_SIGINFO;
	// (void)ac;
	// (void)av;
	// sign.sa_flags = 0;
	input = NULL;

	ft_data_init(&data);
	sign.sa_handler = get_signal;
	while (1)
	{
		if (sigaction(SIGINT, &sign, NULL) == -1)
			return (perror("Error in SIGINT"), -1);
		input = readline("minishell> ");
			// perror("readline() error");
		if (!input)
			if (sigaction(SIGSEGV, &sign, NULL) == -1)
				return (perror("Error in SIGSEGV"), -1);
		if (sigaction(SIGQUIT, &sign, NULL) == -1)
			return (perror("Error in SIGQUIT"), -1);
		if (input && *input)
			add_history(input);
		if (parsing(&data, input) == -1)
		{
			free(input);
			ft_putstr_fd("Wesh ces quoi cette quote\n", 2);
		}
		// ft_cmd(&data);
		free_lst(&data.cmd);
	}
	return (0);
}

/// valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell
