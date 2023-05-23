/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chevrons_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 07:38:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/23 09:20:03 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chevron_error(char *input, int i, char chevron)
{
	if (input[i])
		i++;
	if (input[i] == chevron)
	{	
		if (chevron == '>')
			return (print_error(">>"), 1);
		else
			return (print_error("<<"), 1);
	}
	else
	{
		if (chevron == '>')
			return (print_error(">"), 1);
		else
			return (print_error("<"), 1);
	}
}
