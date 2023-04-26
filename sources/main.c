/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/26 16:25:07 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_exitcode;
// g_exitcode == 0 : nothing particular
// g_exitcode == 1 : signal for newprompt received
// g_exitcode == 2 : process has child
// g_exitcode == 3 : signal for newprompt received and process has a child

void	ft_check_gcode(t_data *data)
{
	if (g_exitcode == 1 || g_exitcode == 3)
	{
		data->exit_code = 130;
		g_exitcode--;
	}
}

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
		ft_check_gcode(&data);
		input_signal(sign);
		input = readline("minishell> ");
		if (!input)
			return (printf("exit\n"), ft_quit(&data, 1), data.exit_code);
		if (ft_strlen(input) > 0) // input && *input)
			add_history(input);
		if (!check_input(input))
		{
			parsing(&data, input);
			ft_cmd(&data);
			free_lst(&data.cmd);
		}
	}
	return (0);
}


		// if (parsing(&data, input) == -1)
		// {
		// 	free(input);
		// 	ft_putstr_fd("Wesh ces quoi cette quote\n", 2);
		// }
