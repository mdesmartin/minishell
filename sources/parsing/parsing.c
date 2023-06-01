/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/01 17:24:18 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_data *data, char *input)
{
	char	**pipes_tab;
	int		nb_pipes;

	nb_pipes = count_pipes(input);
	pipes_tab = NULL;
	pipes_tab = split_pipes(pipes_tab, input, nb_pipes);
	if (!pipes_tab)
		ft_error(data, "Memory allocation failed: pipes_tab in parsing", 12);
	expands(data, pipes_tab);
	if (nb_pipes)
	{
		space_chevron(data, pipes_tab, nb_pipes);
		create_chain(data, &data->cmd, pipes_tab, nb_pipes);
		if (!data->cmd)
			return (1);
		return (0);
	}
	return (1);
}
