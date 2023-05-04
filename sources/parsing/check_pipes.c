/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:10:14 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/04 14:42:06 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_n_end_error(char *input, int i)
{
	char error;

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

//if error return 1
int	check_pipes_n_and(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if ((input[i] == '|' || input[i] == '&') && !in_quotes(input, i))
		return(pipe_n_end_error(input, i), 1);
	return (0);
}

// int second_quote(char *input, int *i, char quote)
// {
// 	(*i)++;
// 	while (input[*i])
// 	{
// 		if (input[*i] == quote)
// 			return (0);
// 		(*i)++;
// 	}
// 	return (1);
// }

// int	check_quotes(char *input)
// {
// 	int	i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'')
// 		{
// 			if (second_quote(input, &i, '\''))
// 				return (1);
// 		}
// 		else if (input[i] == '\"')
// 		{
// 			if (second_quote(input, &i, '\"'))
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }