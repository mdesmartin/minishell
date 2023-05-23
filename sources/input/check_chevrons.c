/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chevrons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:28:34 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/23 10:38:08 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nothing_after(char *input, int i, char chevron)
{
	i++;
	if (input[i] == chevron)
		i++;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!input[i])
		return (1);
	else
		return (0);
}

static int	is_pipe(char *input, int i)
{
	if (input[i] == '|')
	{
		while (input[i])
		{
			i++;
			if (input[i] == '|')
				return (print_error("||"), 1);
		}
		return (print_error("|"), 1);
	}
	return (0);
}

static int	token_error(char *input, int i, char first_chevron)
{
	i++;
	if (input[i] == first_chevron)
		i++;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (is_pipe(input, i))
		return (1);
	else
		return (chevron_error(input, i, input[i]), 1);
}

static int	token_after(char *input, int i, char chevron)
{
	i++;
	if (input[i] == chevron)
		i++;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '<' || input[i] == '>'
		|| input[i] == '|' || input[i] == '&')
		return (1);
	else
		return (0);
}

int	check_chevrons(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>') && !is_in_quotes(input, i)
			&& token_after(input, i, input[i]))
			return (token_error(input, i, input[i]));
		else if ((input[i] == '<' || input[i] == '>') && !is_in_quotes(input, i)
			&& nothing_after(input, i, input[i]))
			return (print_error("newline"), 1);
		i++;
	}
	return (0);
}
