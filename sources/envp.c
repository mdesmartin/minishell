/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:05:59 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/16 11:16:09 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_cp_envp(t_data *data)
{
	extern char	**environ;
	t_envp		*tmp;
	int			i;

	i = 1;
	if (!environ[0])
		ft_printf("Error : Environment not found! ");
	data->envp = malloc(sizeof(t_envp));
	if (!data->envp)
		perror("Error while allocating memory for envp!");
	data->envp->env = ft_strdup(environ[0]);
	while (environ[i])
	{
		tmp = malloc(sizeof(t_envp));
		if (!tmp)
			perror("Error while allocating memory for envp!");
		tmp->env = ft_strdup(environ[i]);
		ft_envadd_back(&data->envp, tmp);
		i++;
	}
}

void	ft_print_env(t_data *data)
{
	t_envp		*tmp;

	tmp = data->envp;
	while (tmp)
	{
		ft_printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
}
