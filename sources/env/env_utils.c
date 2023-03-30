/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:47 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/30 16:54:40 by julien           ###   ########lyon.fr   */
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
			printf("%s=", tmp->variable);
			if (tmp->value)
				printf("\"%s\"\n", tmp->value);
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
			if (ft_strncmp("_", tmp->variable, 2) == 0)
				printf("env");
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

char	**ft_split_var(char *var)
{
	char	**res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_calloc(3, sizeof(char *));
	if (!res)
		perror("Memory allocation failed while spliting envp var!");
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
