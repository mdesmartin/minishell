/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:17:37 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/29 16:48:37 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
