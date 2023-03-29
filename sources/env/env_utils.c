/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:47 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/29 16:39:12 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_data *data)
{
	t_envp		*tmp;

	tmp = data->envp;
	while (tmp)
	{
		ft_printf("declare -x ");
		ft_printf("%s=", tmp->variable);
		if (tmp->value)
			printf("\"%s\"\n", tmp->value);
		else
			printf("\"\"\n");
		tmp = tmp->next;
	}
}

void	ft_print_env(t_data *data)
{
	t_envp		*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
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

char	**ft_lst_to_tabtab(t_envp *envp)
{
	t_envp	*tmp;
	char	**tab;
	int		lstlen;
	int		i;

	i = 0;
	lstlen = ft_envsize(envp);
	tmp = envp;
	tab = ft_calloc(lstlen + 1, sizeof(char *));
	if (!tab)
		return (perror("Memory allocation failed for char **envp!"), NULL);
	while (tmp)
	{
		tab[i] = ft_strjoin3(tmp->variable, "=", tmp->value);
		if (!tab[i])
		{
			perror("Error while copying envp to char **envp_tab!");
			ft_rfree_tab(tab, i);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	tab[lstlen] = NULL;
	return (tab);
}