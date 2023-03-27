/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:48:42 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/25 14:50:13 by julien           ###   ########lyon.fr   */
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
	data->pipes = ft_calloc((data->nb_cmd + 1), sizeof(int *));
	if (!data->pipes)
		perror("ft_calloc failed for data->pipes! ");
	data->cmd = malloc(sizeof(t_list *));
	if (!data->cmd)
		perror("Error while allocating memory for data->cmd! ");
	data->cmd = NULL;
	ft_cp_envp(data);
	data->envp_tab = NULL;
	ft_lst_to_tabtab(data);
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

static int	ft_envsize(t_envp *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lst_to_tabtab(t_data *data)
{
	t_envp	*tmp;
	int		lstlen;
	int		i;

	i = 0;
	lstlen = ft_envsize(data->envp);
	tmp = data->envp;
	data->envp_tab = malloc(lstlen + 1);
	if (!data->envp_tab)
	{
		perror("Error while allocating memory for char **envp!");
		return ;
	}
	data->envp_tab[lstlen] = NULL;
	while (tmp)
	{
		data->envp_tab[i] = ft_strjoin(tmp->variable, ft_strjoin("=", tmp->value));
ft_printf("i = %d\ntmp->variable = %s\ntmp->value = %s\n", i, tmp->variable, tmp->value);
ft_printf("data->envp_tab[%d] = %s\n\n", i, data->envp_tab[i]);
		if (!data->envp_tab[i])
		{
			perror("Error while copying envp to char **envp_tab!");
			ft_rfree_tab(data->envp_tab, i);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
ft_print_envdata(data);
}
