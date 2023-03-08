/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:17:37 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/08 17:17:42 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_signal(int signal)
{
	if (signal == SIGINT)
		printf("control c\n");
	if (signal == SIGSEGV)
		return (printf("control d\n"), exit(-1));
}
