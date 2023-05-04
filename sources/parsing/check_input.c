/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:12:07 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/04 13:10:39 by mehdidesmar      ###   ########lyon.fr   */
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

// if nothing after, newline, else token ' ', ++1 return
int	input_whitespace(char *input)
{
	int i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if (!input || !input[i])
		return (1);
	if (input[i] == ':')
		return (1);
	return (0);
}

int	input_exclamation(char *input)
{
	int	i;

	i = 0;
	if (input[i] == '!')
		return (2);
	return (0);
}

int	check_input(char *input, t_data *data)
{
	if (!(*input))
		return (1);
	if (input_whitespace(input))
		return (data->exit_code = 0, 1);
	if (input_exclamation(input))
		return (data->exit_code = 1, 1);
	if (check_chevrons(input) || check_pipes_n_and(input))
	{
		data->exit_code = 2;
		return (1);
	}
	return (0);
}
