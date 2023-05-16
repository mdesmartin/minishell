/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 23:19:04 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/05/16 14:19:40 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_handler(int flag, char quote)
{
	int double_quote = 0;

	if (quote == '\"')
		double_quote = 1;
	if (flag == (2 + double_quote))
		flag = 6;
	else
		flag = (2 + double_quote);
	return (flag);
}

void	quote_handler(char *token)
{
	int i = 0;
	int j = 0;
	int flag = 6;

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
	return ;
}

void	trim_quotes(char **token_tab)
{
	int i = 0;

	while (token_tab[i])
	{
		quote_handler(token_tab[i]);
		i++;
	}
	return ;
}