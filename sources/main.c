/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/29 13:34:40 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	struct sigaction	sign;
	static char			*input;
	t_data				data;

	sign.sa_handler = get_signal;
	sigemptyset(&sign.sa_mask);
	sign.sa_flags = SA_SIGINFO;
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
