/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/10 10:45:03 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data				data;
	static char			*input;
	t_list				**cmd;
	struct sigaction	sign;

	input = NULL;
data.nb_cmd = 3;
	ft_data_init(&data);

	sign.sa_handler = get_signal;
	cmd = malloc(sizeof(t_list *));
	if (!cmd)
		return (ft_putstr_fd("Error\n", 2), exit(0), -1);
	*cmd = NULL;
	while (1)
	{
		input = readline("minishell> ");
		sigaction(SIGINT, &sign, NULL);
		sigaction(SIGSEGV, &sign, NULL);
		if (!input)
			perror("readline() error");
		printf("Vous avez rentrez : %s\n", input);
		if (input && *input)
			add_history(input);
		ft_process(&data);
		parsing(cmd, input);
		free_lst(cmd);
	}
	return (0);
}

/// valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell