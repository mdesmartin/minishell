/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/31 14:15:48 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	static char			*input;
	struct sigaction	sign;
	t_data				data;

	input = NULL;
	signal_init(sign);
	ft_data_init(&data);
	while (1)
	{
		input = readline("minishell> ");
		if (input && *input)
			add_history(input);
		parsing(&data, input);
		// check_input(input);
		ft_cmd(&data);
		free_lst(&data.cmd);
	}
	return (0);
}


		// if (parsing(&data, input) == -1)
		// {
		// 	free(input);
		// 	ft_putstr_fd("Wesh ces quoi cette quote\n", 2);
		// }
