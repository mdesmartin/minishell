/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/05 20:58:26 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	static char			*input;
	struct sigaction	sign;
	t_data				data;

	input = NULL;
	signal_init(&sign);
	ft_data_init(&data);
	while (1)
	{
		input_signal(sign);
		input = readline("minishell> ");
		if (ft_strlen(input) > 0)// input && *input)
			add_history(input);
		if (!input)
			return (printf("exit\n"), g_exitcode);//free des trucs
		if (!check_input(input))
		{
			parsing(&data, input);
			ft_cmd(&data);
			free_lst(&data.cmd);
		}
		printf("%d\n", g_exitcode);
	}
	return (0);
}


		// if (parsing(&data, input) == -1)
		// {
		// 	free(input);
		// 	ft_putstr_fd("Wesh ces quoi cette quote\n", 2);
		// }
