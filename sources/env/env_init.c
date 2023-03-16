/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:05:59 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/16 16:08:32 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_envp_init(t_data *data)
{
	extern char	**environ;
	char		**buffer;

	if (!environ[0])
		ft_printf("Error : Environment not found! ");
	data->envp = malloc(sizeof(t_envp));
	if (!data->envp)
		perror("Error while allocating memory for envp!");
	buffer = ft_split(environ[0], '=');
	data->envp->variable = ft_strdup(buffer[0]);
	data->envp->value = ft_strdup(buffer[1]);
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
		buffer = ft_split(environ[i], '=');
		tmp->variable = ft_strdup(buffer[0]);
		tmp->value = ft_strdup(buffer[1]);
		tmp->next = NULL;
		free(buffer);
		ft_envadd_back(&data->envp, tmp);
		i++;
	}
}
