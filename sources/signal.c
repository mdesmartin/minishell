/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:17:37 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/10 16:07:03 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ctrl_d()
{
	ft_printf("exit\n");
	exit(0);
}

int	ctrl_c()
{
	// ft_printf("^C\n");
	return (130);
}

int	ctrl_backslash()
{
	return(131);
}

void	get_signal(int signal)
{
	if (signal == SIGINT)
		ctrl_c();
	if (signal == SIGSEGV)
		ctrl_d();
	if (signal == SIGQUIT)
		ctrl_backslash();
}
