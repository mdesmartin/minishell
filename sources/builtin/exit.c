/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:01:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/05 13:40:41 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	ft_convert_exit(t_data *data, char *str)
{
	long long int	i;
	int				str_len;

	str_len = ft_strlen(str);
	if (str_len > 20)
	{
		ft_putstr3_fd("minishell: exit:", str, ": numeric argument required\n");
		ft_quit(data, 2);
	}
	i = ft_atolli(str);
	if ((str_len > 17 && str_len < 20 && i < 1000)
		|| (str_len == 20 && i > -1000))
		ft_putstr3_fd("minishell: exit:", str, ": numeric argument required\n");
	ft_quit(data, (int)((i + 256) % 256));
}

int	ft_check_exitarg(char *code)
{
	int	i;

	i = 0;
	if (code[i] == '+' || code[i] == '-')
		i++;
	while (code[i])
	{
		if (ft_isdigit(code[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_builtin_exit(t_data *data, char **command)
{
	if (!command[1])
		ft_quit(data, 0);
	else if (!command[2])
	{
		if (ft_check_exitarg(command[1]) == 1)
		{
			ft_putstr3_fd("minishell: exit: ",command[1],
				": numeric argument required\n");
			ft_quit(data, 2);
		}
		else
			ft_convert_exit(data, command[1]);
	}
	else
	{
		if (ft_check_exitarg(command[1]) == 1)
		{
			ft_putstr3_fd("minishell: exit: ",command[1],
				": numeric argument required\n");
			ft_quit(data, 2);
		}
		ft_putstr3_fd("minishell: exit:"," ", "too many arguments\n");
		data->exit_code = 1;
	}
}
