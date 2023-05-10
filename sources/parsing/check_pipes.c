/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:10:14 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/09 17:17:47 by mehdidesmar      ###   ########lyon.fr   */
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

int	nothing_after(char *input, int i)
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

//if error return 1
int	check_pipes_n_and(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if ((input[i] == '|' || input[i] == '&') && !in_quotes(input, i))
		return (pipe_n_end_error(input, i), 1);
	while (input[i])
	{
		if ((input[i] == '|' || input[i] == '&') && !in_quotes(input, i) && nothing_after(input, i))
			return(pipe_n_end_error(input, i), 1);
		i++;
	}
	return (0);
}
