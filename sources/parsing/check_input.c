/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:12:07 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/01 22:52:23 by mehdidesmar      ###   ########lyon.fr   */
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


void	print_error(char *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("'\n", 2);
	return ;
}

// if nothing after, newline, else token ' '
int	basic_errors(char *input)
{
	int i;

	i = 0;
	while (is_whitespace(input[i]))
		i++;
	if (!input || !input[i])
		return (1);
	if (input[i] == ':' || input[i] == '!')
		return (1);
	return (0);
}

int	check_input(char *input)
{
	if (!(*input))
		return (1);
	if (basic_errors(input) || check_chevrons(input) || check_pipes_n_and(input))
	{
		// data.exit_code = 2; //need t_data *data
		return (1);
	}
	return (0);
}
