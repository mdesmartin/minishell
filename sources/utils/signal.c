/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:17:37 by mvogel            #+#    #+#             */
/*   Updated: 2023/05/23 16:05:35 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_exitcode;

void	signal_handler(int signum)
{
	if (g_exitcode == 2 || g_exitcode == 3)
		return ;
	if (signum == SIGINT)
	{
		if (g_exitcode == 0)
			g_exitcode++;
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_heredoc(int signum)
{
	if (g_exitcode == 2 || g_exitcode == 3)
		return ;
	if (signum == SIGINT)
	{
		if (g_exitcode == 0)
			g_exitcode++;
		printf("^C\n");
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	signal_init(void (*handler)(int signum))
{
	struct sigaction	sign;

	sigemptyset(&sign.sa_mask);
	sign.sa_flags = SA_RESTART;
	sign.sa_handler = handler;
	rl_catch_signals = 0;
	sigaction(SIGINT, &sign, NULL);
	sigaction(SIGQUIT, &sign, NULL);
}
