/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:12:07 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/05 13:59:51 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_quote(void)
{
	ft_putstr_fd("minishell: syntax error quote not closed\n", 2);
}

void	print_error(char *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("'\n", 2);
	return ;
}

// if nothing after, newline, else token ' ', ++1 return
static int	check_whitespace(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if (!input || !input[i])
		return (1);
	if (input[i] == ':')
		return (1);
	return (0);
}

static int	check_exclamation(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if (input[i] == '!')
		return (1);
	return (0);
}

int	check_input(char *input, t_data *data)
{
	if (!(*input))
		return (1);
	if (check_whitespace(input))
		return (data->exit_code = 0, 1);
	if (check_exclamation(input))
		return (data->exit_code = 1, 1);
	if (nb_pipes(input) == -1)
		return (data->exit_code = 2, error_quote(), 1);
	if (check_chevrons(input) || check_pipes_n_and(input))
		return (data->exit_code = 2, 1);
	return (0);
}
