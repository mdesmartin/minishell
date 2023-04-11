/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:42:33 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/11 11:11:21 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_cmdjoin(char **tab)
{
	char	*buffer;
	char	*cmd_arg;
	int		i;

	i = 1;
	cmd_arg = ft_strdup(tab[0]);
	while (tab[i])
	{
		buffer = cmd_arg;
		cmd_arg = ft_strjoin3(buffer, " ", tab[i]);
		free(buffer);
		if (!cmd_arg)
		{
			perror("Error when allocating memory in get_direction! ");
			return (NULL);
		}
		i++;
	}
	return (cmd_arg);
}

void	get_rediction(t_data *data, int i)
{
	t_data		*tmp;
	t_pipeline	*pipe;
	char		*cmd_arg;

	tmp = data;
	while (i > 0)
	{
		tmp->cmd = tmp->cmd->next;
		i--;
	}
	pipe = s_read_cnt(tmp->cmd);
	cmd_arg = ft_cmdjoin(pipe->command);
	if (!cmd_arg)
		ft_quit(data, 1);
	ft_extract_inputredir(pipe, cmd_arg);
	ft_extract_outputredir(pipe, cmd_arg);
}

// cat valgrind_ignore_leaks.txt <aaaa > bbbbb << cccc >> ddddd

// static void	ft_del_redirec(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '>')
// 			str[i] = ' ';
// 		i++;
// 	}
// }
