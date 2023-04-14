/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:14:28 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/04/12 23:45:03 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_word_len(char const *s, int *i)
{
	int	len;

	len = 0;
	while (s[*i] && s[*i] != ' ')
	{
		(*i)++;
		len++;
	}
	return (len);
}

void	skip_quote(char *input, int *i)
{
	if (input[*i] == '\'')
		find_quote(input, i, '\'');
	if (input[*i] == '\"')
		find_quote(input, i, '\"');
	(*i)++;
	return ;
}

int	skip_chevron(char *pipe, int *i)
{
	int	k = 0;
	char	*chevron[] = {"<<", ">>", "<", ">"};

	while (chevron[k])
	{
		if (k < 2)
		{
			if (!ft_strncmp(chevron[k], pipe + *i, 2))
				return (k + 1);
		}
		else
		{
			if (!ft_strncmp(chevron[k], pipe + *i, 1))
				return (k + 1);
		}
	}
	return (0);
}

char	*add_chev(int chevron)
{
	char	*symbol[] = {"<<", ">>", "<\n", ">\n"};

	return (symbol[chevron - 1]);
}

// je prend pas du tot le mot en entier ?ou je i++
char	**split_token(char **token_tab, char *pipe)
{
	int	i;
	int	j;
	int chevron;

	i = 0;
	j = 0;
	chevron = 0;
	while(pipe[i])
	{
		skip_quote(pipe, &i);
		chevron = skip_chevron(pipe, &i);
		if (!chevron)
			token_tab[j] = ft_substr(pipe, i, ft_word_len(pipe, &i));//protect
		else
			token_tab[j] = ft_substr(add_chev(chevron), i, 2);//protect
		// i++;?
		j++;
	}
	return (token_tab);
}

int	count_chevron(char *pipe, int *i)
{
	int nb = 0;

	while (pipe[*i])
	{
		while (pipe[*i] != '>' || pipe[*i] != '<')
		{
			(*i)++;
			nb++;
		}
	}
	return (1);
}

char	**token_tab(char *pipe)
{
	char	**token_tab;
	// int		nb_token;

	// nb_token = count_token(pipe);
	token_tab = NULL;
	token_tab = ft_calloc(sizeof(char *), (ft_strlen(pipe) * 2));
	if (!token_tab)
		return (ft_putstr_fd("error creating tab\n", 2), NULL);
	token_tab = split_token(token_tab, pipe);
	return (token_tab);
}




// int	count_token(char *pipe)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 1;
// 	while (pipe[i] == ' ')
// 		i++;
// 	while (pipe[i])
// 	{
// 		skip_quote(pipe, &i);
// 		while (pipe[i] == ' ')
// 			i++;
// 		if (pipe[i] != '>' || pipe[i] != '<')
// 			count += count_chevron(pipe, &i);
// 		else
// 		{
// 			count++;
// 			i++;
// 		}
// 	}
// 	return (count);
// }
