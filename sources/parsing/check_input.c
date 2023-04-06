/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:12:07 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/04/06 13:32:25 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("'\n", 2);
	return ;
}

// if nothing after, newline, else token ' '

int	basic_error(char *input)
{
	int	i;

	i = 0;
	if (!input[i] || !(*input))
		return (1);
	while (input[i] == '	' || input[i] == ' ')
		i++;
	// if (!input[i] || input[i] == ':' || input[i] == '!')
	// {
	// 	if (input[i] == '!')
	// 		g_exitcode = 1;
	// 	else
	// 		g_exitcode = 0;
	// 	return (1);
	// }
	if (check_chevron(input, &i))
	{
		// data.exit_code = 2; //need t_data *data
		return (1);
	}
	// if (check_chevron)
	return (0);
}

int	check_input(char *input)
{
	// int	i;

	// i = 0;
	// while (input[i])
	// {}
	if (!(*input))
		return (1);
	if (basic_error(input))
		return (1);
	return (0);
}

// "" | ls~