/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:45:12 by mvogel            #+#    #+#             */
/*   Updated: 2023/06/05 14:05:55 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	revert_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == -39)
			line[i] = '\'';
		else if (line[i] == -34)
			line[i] = '\"';
		i++;
	}
}
