/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chevrons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:28:34 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/22 16:10:16 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int	unexpected_chevron(char *input, int *i, char chevron)
// {
// 	(*i)++;
// 	if (input[*i] == chevron)
// 	{	
// 		if (chevron == '>')
// 			return (print_error(">>"), 1);
// 		else
// 			return (print_error("<<"), 1);
// 	}
// 	else
// 	{
// 		if (chevron == '>')
// 			return (print_error(">"), 1);
// 		else
// 			return (print_error("<"), 1);
// 	}
// }

// static int	is_pipe(char *input, int *i)
// {	
// 	if (input[*i] == '|')
// 	{
// 		while (input[*i])
// 		{
// 			(*i)++;
// 			if (input[*i] == '|')
// 				return (print_error("||"), 1);
// 		}
// 		return (print_error("|"), 1);
// 	}
// 	return (0);
// }

// static int	is_chevron(char *input, int *i)
// {
// 	(*i)++;
// 	while (input[*i])
// 	{
// 		if (input[*i] == '<' || input[*i] == '>')
// 			(*i)++;
// 		while (input[*i] == ' ')
// 			(*i)++;
// 		if (is_pipe(input, i))
// 			return (1);
// 		if (input[*i] != '|' && (input[*i] >= 33 && input[*i] <= 126))
// 			return (0);
// 		else if (input[*i] == '>')
// 		{
// 			if (unexpected_chevron(input, i, '>'))
// 				return (1);
// 		}
// 		else if (input[*i] == '<')
// 		{
// 			if (unexpected_chevron(input, i, '<'))
// 				return (1);
// 		}
// 		if (input[*i])
// 			(*i)++;
// 	}
// 	return (print_error("newline"), 1);
// }

// int	check_chevrons(char *input)
// {
// 	int	i;

// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '<' && !in_quotes(input, i))
// 		{
// 			if (is_chevron(input, &i))
// 				return (1);
// 		}
// 		else if (input[i] == '>' && !in_quotes(input, i))
// 		{
// 			if (is_chevron(input, &i))
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }







// si (<, >, <<, >>, <>) et rien apres space -- newline
// mais si (<>) et pas de signe cole trim le signe et ce qui suit jusqu'au pipe/end
// mais si apres y a un autre signe (soit different du premier soit a partir du troisieme du meme -- token
// compter de maniere speciale jusqua espace 




// static int	chevron_error(char *input, int *i)
// {
// 	(*i)++;
// 	if (input[*i] == '<' || input[*i] == '>')
//  		(*i)++;

// }


static int	unexpected_chevron(char *input, int i, char chevron)
{
	if (input[i])
		i++;
	if (input[i] == chevron)
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

static int	nothing_after(char *input, int i, char chevron)
{
	i++;
	if (input[i] == chevron)
		i++;
	while (input[i])
	{
		// printf("ok");
		if (input[i] != ' ' && input[i] != '\n')
			return (printf("ok\n"), 0);
		i++;
	}
	return (1);
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
		return (unexpected_chevron(input, i, input[i]), 1);
}

static int	token_after(char *input, int i, char chevron)
{
	i++;
	if (input[i] == chevron)
		i++;
	while (input[i] == ' ' || input[i] == '\t')
		i++;	
	if (input[i] == '<' && input[i] == '>'
		&& input[i] == '|' && input[i] == '&')
		return (1);
	return (0);
}

int	check_chevrons(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>') && !in_quotes(input, i) && nothing_after(input, i, input[i]))//nothing_after(input, i, input[i]))
			return (print_error("newlinee"), 1);
		else if ((input[i] == '<' || input[i] == '>') && !in_quotes(input, i) && token_after(input, i, input[i]))
			return (token_error(input, i, input[i]));
		i++;
	}
	return (0);
}
