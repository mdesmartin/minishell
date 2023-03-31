/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:52:20 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/31 13:47:25 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_builtin_export(t_data *data)
{
	if (s_read_cnt(data->cmd)->command[1] == NULL)
		ft_print_export(data);
	else
		ft_export(data);
}

static void	ft_builtin_unset(t_data *data)
{
	if (s_read_cnt(data->cmd)->command[1] == NULL)
		return ;
	else
		ft_unset(data);
}

static void	ft_builtin_pwd(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->variable, 4) == 0)
			break ;
		tmp = tmp->next;
	}
	printf("%s\n", tmp->value);
}

static void	ft_builtin_echo(t_data *data)
{
	int	i;

	i = 1;
	if (ft_strncmp("-n", s_read_cnt(data->cmd)->command[1], 3) == 0)
		i++;
	while (s_read_cnt(data->cmd)->command[i])
	{
		printf("%s", (char *) s_read_cnt(data->cmd)->command[i]);
		i++;
		if (s_read_cnt(data->cmd)->command[i])
			printf(" ");
	}
	if (ft_strncmp("-n", s_read_cnt(data->cmd)->command[1], 3) != 0)
		printf("\n");
}

int	ft_builtin(t_data *data)
{
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "cd", 3) == 0)
		return (ft_builtin_cd(data), 1);
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "exit", 5) == 0)
		return (ft_quit(data), exit(0), 1);
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "echo", 5) == 0)
		return (ft_builtin_echo(data), 1);
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "env", 4) == 0)
		return (ft_print_env(data), 1);
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "pwd", 4) == 0)
		return (ft_builtin_pwd(data), 1);
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "export", 7) == 0)
		return (ft_builtin_export(data), 1);
	if (ft_strncmp(s_read_cnt(data->cmd)->command[0], "unset", 6) == 0)
		return (ft_builtin_unset(data), 1);
	return (0);
}
