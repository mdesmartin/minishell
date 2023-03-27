/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:06:47 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/25 14:46:08 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envp	*ft_envlast(t_envp *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_envadd_back(t_envp **lst, t_envp *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_envlast(*lst)->next = new;
	return ;
}

void	ft_print_export(t_data *data)
{
	t_envp		*tmp;

	tmp = data->envp;
	while (tmp)
	{
		ft_printf("declare -x ");
		ft_printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_print_env(t_data *data)
{
	t_envp		*tmp;

	tmp = data->envp;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
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

void	ft_print_envdata(t_data *data)
{
	t_envp		*tmp;
	int			i;

	i = 0;
	tmp = data->envp;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->variable, tmp->value);
		ft_printf("data->envp_tab[%d] = %s\n\n", i, data->envp_tab[i]);
		tmp = tmp->next;
		i++;
	}
}
