/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:10:14 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/06/01 13:07:39 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_n_end_error(char *input, int i)
{
	char	error;

	error = input[i];
	i++;
	if (input[i] != '\0' && input[i] == error)
	{
		if (error == '|')
			return (print_error("||"));
		else
			return (print_error("&&"));
	}
	else
	{
		if (error == '|')
			return (print_error("|"));
		else
			return (print_error("&"));
	}
}

static int	nothing_after(char *input, int i)
{
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\n'
			&& input[i] != '|' && input[i] != '&')
			return (0);
		i++;
	}
	return (1);
}

int	double_pipe(char *input, int i)
{
	i++;
	if (input[i] && input[i] == '|')
		return (1);
	else
		return (0);
}

int	check_pipes_n_ampersand(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if ((input[i] == '|' || input[i] == '&') && !is_in_quotes(input, i))
		return (pipe_n_end_error(input, i), 1);
	while (input[i])
	{
		if ((input[i] == '|' || input[i] == '&') \
		&& !is_in_quotes(input, i) && nothing_after(input, i))
			return (pipe_n_end_error(input, i), 1);
		else if (input[i] == '|' && !is_in_quotes(input, i) \
		&& (nothing_after(input, i) || double_pipe(input, i)))
			return (pipe_n_end_error(input, i + 1), 1);
		i++;
	}
	return (0);
}
