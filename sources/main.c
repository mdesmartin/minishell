/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/10 16:52:39 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char** av, char **envp)
{
	struct sigaction	sign;
	static char			*input;
	t_data				data;

	(void)ac;
	(void)av;
	input = NULL;
	ft_data_init(&data, envp);
	sign.sa_handler = get_signal;
	while (1)
	{
		input = readline("minishell> ");
		sigaction(SIGINT, &sign, NULL); //if -1 perror
		sigaction(SIGSEGV, &sign, NULL);
		if (!input)
			perror("readline() error");
		if (input && *input)
			add_history(input);
		parsing(&data, input);
		ft_process(&data);
		free_lst(&data.cmd);
	}
	return (0);
}




/// valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell