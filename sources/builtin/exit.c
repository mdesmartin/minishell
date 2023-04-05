/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:01:55 by julien            #+#    #+#             */
/*   Updated: 2023/04/05 13:03:56 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exitcode;

static long long int	ft_atolli(const char *str)
{
	unsigned long long int	res;
	int						i;
	int						sign;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((long long int) res * sign);
}

void	ft_convert_exit(char *str)
{
	long long int	i;
	int				str_len;

	str_len = ft_strlen(str);
	if (str_len > 20)
	{
		ft_putstr3_fd("minishell: exit:", str, ": numeric argument required\n");
		ft_exit(2);
	}
	i = ft_atolli(str);
	if ((str_len > 17 && str_len < 20 && i < 1000)
		|| (str_len == 20 && i > -1000))
		ft_putstr3_fd("minishell: exit:", str, ": numeric argument required\n");
// printf("exit code = %d\n", (int) ((i + 256) % 256));
	ft_exit((int)((i + 256) % 256));
}

void	ft_exit(int exit_code)
{
	g_exitcode = exit_code;
	exit(exit_code);
}

int	ft_check_exitarg(char *code)
{
	int	i;

// printf("ft_check_exitarg(\"%s\")\n", code);
	i = 0;
	if (code[i] == '+' || code[i] == '-')
		i++;
	while (code[i])
	{
// printf("ft_isdigit(%c) = %d\n", code[i], ft_isdigit(code[i]));
		if (ft_isdigit(code[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_builtin_exit(t_data *data)
{
	if (!s_read_cnt(data->cmd)->command[1])
	{
		ft_quit(data);
		ft_exit(0);
	}
	if (!s_read_cnt(data->cmd)->command[2])
	{
		if (ft_check_exitarg(s_read_cnt(data->cmd)->command[1]) == 1)
		{
			ft_putstr3_fd("minishell: exit: ",s_read_cnt(data->cmd)->command[1],
				": numeric argument required\n");
			ft_exit(2);
		}
		else
			ft_convert_exit(s_read_cnt(data->cmd)->command[1]);
	}
	ft_putstr3_fd("minishell: exit:"," ", "too many arguments\n");
	g_exitcode = 1;
}
