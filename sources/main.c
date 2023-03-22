/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/16 13:44:43 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	struct sigaction	sign;
	static char			*input;
	t_data				data;

	// sign = { 0 };
	sign.sa_handler = get_signal;
	// sign.sa_sigaction = NULL;
	sigemptyset(&sign.sa_mask);
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
		parsing(&data, input);
		ft_cmd(&data);
		free_lst(&data.cmd);
	}
	return (0);
}

/// valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell
