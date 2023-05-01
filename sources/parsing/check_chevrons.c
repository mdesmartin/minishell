/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chevrons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:28:34 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/01 23:18:32 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unexpected_chevron(char *input, int *i, char chevron)
{
	(*i)++;
	if (input[*i] == chevron)
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

int	is_pipe(char *input, int *i)
{	
	if (input[*i] == '|')
	{
		while (input[*i])
		{
			(*i)++;
				if (input[*i] == '|')
					return (print_error("||"), 1);
		}
		return (print_error("|"), 1);
	}
	return (0);
}

int	is_chevron(char *input, int *i)
{
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == '<' || input[*i] == '>')
			(*i)++;
		while (input[*i] == ' ')
			(*i)++;
		if (ft_isalnum(input[*i]))// != '\0' && (input[*i] != '>' || input[*i] != '<'))//check ce quil y a apres space
			return (0);
		else if (is_pipe(input, i))
			return (1);
		else if (input[*i] == '>')
		{
			if (unexpected_chevron(input, i, '>'))
				return (1);
		}
		else if (input[*i] == '<')
		{
			if (unexpected_chevron(input, i, '<'))
				return (1);
		}
		(*i)++;
	}
	return (print_error("newline"), 1);
}

int	check_chevrons(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && !in_quotes(input, i))
		{
			if (is_chevron(input, &i))
				return (1);
		}
		else if (input[i] == '>' && !in_quotes(input, i))
		{
			if (is_chevron(input, &i))
				return (1);
		}
		i++;
	}
	return (0);
}
