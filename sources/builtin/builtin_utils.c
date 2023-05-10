/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:21:55 by julien            #+#    #+#             */
/*   Updated: 2023/05/09 16:23:04 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_exitcode;

void	ft_putstr3_fd(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

void	ft_update_envptab(t_data *data)
{
	ft_free_envptab(data);
	data->envp_tab = ft_lst_to_tabtab(data, data->envp);
}

int	ft_check_exportopt(t_data *data, char *command1)
{
	if (ft_strncmp("-", command1, 1) == 0)
	{
		ft_putstr_fd("minishell : export: `", 2);
		ft_putchar_fd(command1[0], 2);
		ft_putchar_fd(command1[1], 2);
		ft_putstr_fd("': options are not supported\n", 2);
		data->exit_code = 1;
		return (1);
	}
	return (0);
}

int	ft_check_exportvar(char *variable)
{
	int	i;

	i = 1;
	if (variable[0] == '='
		|| (ft_isalpha(variable[0]) == 0 && variable[0] != '_'))
	{
		ft_putstr_fd("minishell : export: `", 2);
		ft_putstr_fd(variable, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	while (variable[i] && variable[i] != '=')
	{
		if (ft_isalnum(variable[i]) == 0 && variable[i] != '_')
		{
			ft_putstr_fd("minishell : export: `", 2);
			ft_putstr_fd(variable, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_builtin_slash(t_data *data, char *directory)
{
	if (access(directory, F_OK) == -1)
	{
		ft_putstr3_fd("minishell: ", directory, ": ");
		perror(NULL);
		ft_quit(data, 0);
	}
	else if (access(directory, X_OK) == -1)
	{
		ft_putstr3_fd("minishell: ", directory, ": ");
		perror(NULL);
		ft_quit(data, 0);
	}
	else
	{
		ft_putstr3_fd("minishell: ", directory, ": Is a directory\n");
		ft_quit(data, 126);
	}
}


