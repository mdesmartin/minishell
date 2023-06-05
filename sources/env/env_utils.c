/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:47 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/05 14:51:33 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(t_data *data)
{
	t_envp		*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_strncmp("_", tmp->variable, 2) != 0)
		{
			printf("declare -x ");
			printf("%s", tmp->variable);
			if (tmp->value)
				printf("=\"%s\"\n", tmp->value);
			else if (tmp->value == NULL)
				printf("\n");
			else
				printf("\"\"\n");
		}
		tmp = tmp->next;
	}
}

void	ft_print_env(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (tmp->value)
		{
			printf("%s=%s", tmp->variable, tmp->value);
			printf("\n");
		}
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

static void	ft_strjoin3_error(t_data *data, char **tab, int i)
{
	ft_rfree_tab(tab, i);
	ft_error(data, "Memory allocation failed: char **envp!", 12);
}

char	**ft_lst_to_tabtab(t_data *data, t_envp *envp)
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
		ft_error(data, "Memory allocation failed: char **envp!", 12);
	while (tmp)
	{
		if (tmp->value)
		{
			tab[i] = ft_strjoin3(tmp->variable, "=", tmp->value);
			if (!tab[i])
				ft_strjoin3_error(data, tab, i);
			i++;
		}
		tmp = tmp->next;
	}
	tab[lstlen] = NULL;
	return (tab);
}
