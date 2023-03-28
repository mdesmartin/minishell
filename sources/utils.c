/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:42 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/28 14:20:40 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_c_in(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_data_init(t_data *data)
{
	data->nb_cmd = 0;
	data->pipes = NULL;
	data->cmd = NULL;
	ft_cp_envp(data);
	data->envp_tab = ft_lst_to_tabtab(data->envp);
}

void	ft_close_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*res;
	char	*tmp;

	if (!s1 && !s2 && !s3)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (perror("Error while allocating memory for char **envp!"), NULL);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	if (!res)
		return (perror("Error while allocating memory for char **envp!"), NULL);
	return (res);
}

void	ft_print_tabtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("env[%d]\t=\t%s\n", i, tab[i]);
		i++;
	}
}
