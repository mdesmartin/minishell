/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:31 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/08 17:10:31 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data		data;
	static char	*input;

	input = NULL;
data.nb_cmd = 3;
	ft_data_init(&data);
	printf("%s\n", ft_get_arg_path(&data));
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			perror("readline() error");
		printf("Vous avez rentrez : %s\n", input);
		if (input && *input)
			add_history(input);
		free(input);
		ft_process(&data);
	}
	return (0);
}
