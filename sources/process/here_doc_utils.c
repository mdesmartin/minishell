/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:00:26 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/23 13:42:04 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_hd_expand(t_data *data, char *limiter)
{
	if (limiter[0] < 0)
	{
		data->here_doc_expand = 1;
		limiter[0] *= -1;
	}
	else
		data->here_doc_expand = 0;
}

