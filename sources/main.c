/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/06 13:06:25 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
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
			return (printf("exit\n"), data.exit_code);//free des trucs
		if (!check_input(input))
		{
			parsing(&data, input);
			ft_cmd(&data);
			free_lst(&data.cmd);
		}
		printf("%d\n", data.exit_code);
	}
	return (0);
}


		// if (parsing(&data, input) == -1)
		// {
		// 	free(input);
		// 	ft_putstr_fd("Wesh ces quoi cette quote\n", 2);
		// }
