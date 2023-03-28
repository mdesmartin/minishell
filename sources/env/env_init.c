/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:05:59 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/28 15:22:52 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split_var(char *var)
{
	char	**res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_calloc(3, sizeof(char *));
	tmp = var;
	while (tmp && *tmp != '=')
	{
		tmp++;
		i++;
	}
	if (*tmp == '=')
		tmp++;
	res[0] = ft_substr(var, 0, i);
	res[1] = ft_strdup(tmp);
	return (res);
}

static void	ft_envp_init(t_data *data)
{
	extern char	**environ;
	char		**buffer;

	if (!environ[0])
		ft_printf("Error : Environment not found! ");
	data->envp = malloc(sizeof(t_envp));
	if (!data->envp)
		perror("Error while allocating memory for envp!");
	buffer = ft_split_var(environ[0]);
	data->envp->variable = buffer[0];
	data->envp->value = buffer[1];
	data->envp->next = NULL;
	free(buffer);
}

void	ft_cp_envp(t_data *data)
{
	extern char	**environ;
	t_envp		*tmp;
	char		**buffer;
	int			i;

	i = 1;
	ft_envp_init(data);
	while (environ[i])
	{
		tmp = malloc(sizeof(t_envp));
		if (!tmp)
			perror("Error while allocating memory for envp!");
		buffer = ft_split_var(environ[i]);
		tmp->variable = buffer[0];
		tmp->value = buffer[1];
		tmp->next = NULL;
		free(buffer);
		ft_envadd_back(&data->envp, tmp);
		i++;
	}
}
