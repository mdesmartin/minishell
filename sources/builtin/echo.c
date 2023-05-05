/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:17:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/05 13:33:24 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_echo_opt(char *command)
{
	int	i;

	i = 2;
	while (command[i])
	{
		if (command[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_builtin_echo(char **command)
{
	int	i;

	i = 1;
	if (!command[1])
	{
		printf("\n");
		return ;
	}
	while (command[i] && ft_strncmp("-n", command[i], 2) == 0
		&& ft_check_echo_opt(command[i]) == 0)
		i++;
	while (command[i])
	{
		printf("%s", command[i]);
		i++;
		if (command[i])
			printf(" ");
	}
	if (ft_strncmp("-n", command[1], 2) != 0
		|| ft_check_echo_opt(command[1]) == 1)
		printf("\n");
}
