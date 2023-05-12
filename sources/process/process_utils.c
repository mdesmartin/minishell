/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:55:39 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/11 16:59:35 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_fds(t_data *data, int *here_doc_fd)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	if (here_doc_fd)
	{
		close(here_doc_fd[0]);
		close(here_doc_fd[1]);
	}
}

char	*ft_getenv(t_envp *envp, char *variable)
{
	t_envp	*tmp;
	int		n;

	tmp = envp;
	n = ft_strlen(variable) + 1;
	while (tmp)
	{
		if (ft_strncmp(variable, tmp->variable, n) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
