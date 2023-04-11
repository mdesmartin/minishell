/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:27:28 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/04/10 11:37:08 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_arrow(char *c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (3);
	return (0);
}

int	get_type(char *pipe_tab)
{
	int	i;
	int	type;

	type = 0;
	while (pipe_tab[i])
	{
		while (!type)
		{
			type = is_arrow(pipe_tab[i]);
			i++;
		}
		i++;
		type += is_arrow(pipe_tab[i]);
	}
	return (type);
}

char	*get_file(pipe_tab);

int	redirection(data, pipe_tab)
{
	int	type;

	type = get_type(pipe_tab);
	file = get_file(pipe_tab);
	input
}