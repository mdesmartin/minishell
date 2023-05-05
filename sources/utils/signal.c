/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:17:37 by mvogel            #+#    #+#             */
/*   Updated: 2023/05/05 15:44:03 by mehdidesmar      ###   ########lyon.fr   */
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
		// ioctl(STDIN_FILENO, TIOCSTI, "\n");
		printf("\n");
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
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
// printf("Fuck minishell\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_redisplay();
	}
}

void	signal_init(void (*handler)(int signum))
{
	struct sigaction	sign;

	// sigemptyset(&sign->sa_mask);
	sign.sa_flags = SA_RESTART;
	sign.sa_handler = handler;
	rl_catch_signals = 0;
	sigaction(SIGINT, &sign, NULL);
	sigaction(SIGQUIT, &sign, NULL);
}

// void	sig_handler_child(int signum)
// {
// 	if (signum == SIGINT)
// 		g_exitcode = 1;
// }

// void	sig_init(void (*handler)(int))
// {
// 	struct sigaction	act;

// 	act.sa_flags = SA_RESTART;
// 	act.sa_handler = handler;
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGQUIT, &act, NULL);
// }

// void	exec_ctrl_c()
// {
// 	printf("\n");
// 	g_exitcode = 130;
// }
// void	exec_signal()
// {
// 	signal(SIGINT, exec_ctrl_c);
// 	signal(SIGQUIT, ctrl_backslash);
// }

// void	input_signal()
// {
// 	signal(SIGINT, ctrl_c);
// 	signal(SIGQUIT, SIG_IGN);
// }