/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 23:19:04 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/23 10:42:17 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	flag_handler(int flag, char quote)
{
	int	double_quote;

	double_quote = 0;
	if (quote == '\"')
		double_quote = 1;
	if (flag == (2 + double_quote))
		flag = 6;
	else
		flag = (2 + double_quote);
	return (flag);
}

static void	trim_quote(char *token)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 6;
	while (token[i])
	{
		if (token[i] == '\'' && flag % 2 == 0)
			flag = flag_handler(flag, token[i]);
		else if (token[i] == '\"' && flag % 3 == 0)
			flag = flag_handler(flag, token[i]);
		else
		{
			token[j] = token[i];
			j++;
		}
		i++;
	}
	while (token[j])
	{
		token[j] = '\0';
		j++;
	}
}

static void	convert_redirection(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '<' && !is_in_quotes(token, i))
			token[i] = -60;
		else if (token[i] == '>' && !is_in_quotes(token, i))
			token[i] = -62;
		i++;
	}
}

void	token_parsing(char **token_tab)
{
	int	i;

	i = 0;
	while (token_tab[i])
	{
		convert_redirection(token_tab[i]);
		trim_quote(token_tab[i]);
		i++;
	}
	return ;
}
