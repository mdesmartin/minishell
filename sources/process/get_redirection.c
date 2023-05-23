/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:42:33 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/22 12:42:08 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_redirection(t_data *data, int i)
{
	t_list	*tmp;
	char	**redirections;

	tmp = data->cmd;
	while (i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	redirections = (char **)s_read_cnt(tmp)->redirections;
	ft_apply_redirection(data, redirections);
	return ((char **)s_read_cnt(tmp)->command);
}

void	ft_free_two_line(char **tab, int i)
{
	free(tab[i]);
	free(tab[i + 1]);
	while (tab[i + 2])
	{
		tab[i] = tab[i + 2];
		if (tab[i + 3])
			tab[i + 1] = tab[i + 3];
		else
		{
			tab[i + 1] = NULL;
			return ;
		}
		i += 2;
	}
	tab[i] = NULL;
	tab[i + 1] = NULL;
}

static void	ft_del_input(char **cmd, int i)
{
	if (cmd[i][0] == -60 && ft_strlen(cmd[i]) == 1)
		ft_free_two_line(cmd, i);
	else if (cmd[i][0] == -60 && cmd[i][1] == -60 && ft_strlen(cmd[i]) == 2)
		ft_free_two_line(cmd, i);
}

static void	ft_del_output(char **cmd, int i)
{
	if (cmd[i][0] == -62 && ft_strlen(cmd[i]) == 1)
		ft_free_two_line(cmd, i);
	else if (cmd[i][0] == -62 && cmd[i][1] == -62 && ft_strlen(cmd[i]) == 2)
		ft_free_two_line(cmd, i);
}

void	ft_del_redirections(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i][0] == -60 && ft_strlen(cmd[i]) == 1)
			|| (cmd[i][0] == -60 && cmd[i][1] == -60 && ft_strlen(cmd[i]) == 2))
		{
			ft_del_input(cmd, i);
			i = -1;
		}
		else if ((cmd[i][0] == -62 && ft_strlen(cmd[i]) == 1)
			|| (cmd[i][0] == -62 && cmd[i][1] == -62 && ft_strlen(cmd[i]) == 2))
		{
			ft_del_output(cmd, i);
			i = -1;
		}
		i++;
	}
}
