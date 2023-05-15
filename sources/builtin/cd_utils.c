/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:00:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/15 10:56:05 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static char	*ft_get_home(t_data *data)
// {
// 	t_envp	*tmp;

// 	tmp = data->envp;
// 	while (tmp)
// 	{
// 		if (ft_strncmp("HOME", tmp->variable, 5) == 0)
// 			break ;
// 		tmp = tmp->next;
// 	}
// 	if (tmp && !tmp->value)
// 	{
// 		ft_putstr_fd("minishell: cd : HOME not set!\n", 2);
// 		data->exit_code = 1;
// 		return (tmp->value);
// 	}
// 	return (NULL);
// }

void	ft_cd_home(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("HOME", tmp->variable, 5) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp || (tmp && !tmp->value))
	{
		ft_putstr_fd("minishell: cd : HOME not set!\n", 2);
		data->exit_code = 1;
		return ;
	}
	else if (tmp->value[0] == '\0')
		return ;
	if (chdir(tmp->value) == -1)
		ft_perror(data, "minishell: cd", 1);
}

void	ft_cd_back(t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_getenv(data->envp, "OLDPWD");
	if (chdir(oldpwd) == -1)
		ft_perror(data, "minishell: cd", 1);
}

void	ft_cd_opt(t_data *data, char *command1)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putchar_fd(command1[0], 2);
	ft_putchar_fd(command1[1], 2);
	ft_putstr_fd(": options are not supported\n", 2);
	data->exit_code = 2;
}
