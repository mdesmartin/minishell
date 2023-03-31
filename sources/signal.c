/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:17:37 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/31 14:13:41 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_init(struct sigaction sign)
{
	sign.sa_handler = get_signal;
	sigemptyset(&sign.sa_mask);
	sign.sa_flags = SA_SIGINFO;
	sign.sa_handler = get_signal;
	return ;
}

		// if (!input)
		// 	if (sigaction(SIGSEGV, &sign, NULL) == -1)
		// 		return (perror("Error in SIGSEGV"), -1);
		// if (sigaction(SIGINT, &sign, NULL) == -1)
		// 	return (perror("Error in SIGINT"), -1);
		// 	// perror("readline() error");
		// if (sigaction(SIGQUIT, &sign, NULL) == -1)
		// 	return (perror("Error in SIGQUIT"), -1);

int	ctrl_d()
{
	printf("exit\n");
	exit(0);
}

int	ctrl_c()
{
	// printf("^C\n");
	return (130);
}

int	ctrl_backslash()
{
	return(131);
}

void	get_signal(int signal)
{
	// if (signal == SIGINT)
	// 	ctrl_c();
	if (signal == SIGSEGV)
		ctrl_d();
	if (signal == SIGQUIT)
		ctrl_backslash();
}
