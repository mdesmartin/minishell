/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:06:52 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/04/12 21:37:06 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// do split with spaces, implant before and after word whiler space, then chevron should be serounded by spaces
// fisrt transform sentence by adding spacesd betwen chevron when it should be there, then split spaces,
//pb many spaces, wrong count only here

//work: split before and after < > << >> or " " or "	"


void	skip_quote(char *input, int *i)
{
	if (input[*i] == '\'')
		find_quote(input, i, '\'');
	if (input[*i] == '\"')
		find_quote(input, i, '\"');
	return ;
}

int	put_chevron(char *str, int *i)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		if (str[*i] == '>' || str[*i] == '<')
			return (2);
		else
		{
			i--;
			return (1);
		}
	}
	return (0);
}

char	*split_chevron(char *str)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc((ft_strlen(str)) * 2, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (str[i] == '<' || str[i] == '>')
		{
			new[j++] = ' ';
			if (str[++i] == '<' || str[++i] == '>')
				new[j++] = str[i];
			new[j++] = str[i];
			new[j++] = ' ';
		}
		else
			new[j] = str[i];
		j++;
		i++;
	}
	return (new);
}

int	count_token(char *input, char separator)
{
	int	nb_token;
	int	i;

	i = 0;
	nb_token = 0;
	while (input[i])
	{
		while (input[i] == separator)
			i++;
		if (input[i])
			nb_token++;
		while (input[i] != separator && input[i])
		{
			skip_quote(input, &i);
			i++;
		}
	}
	return (nb_token);
}

char	**create_command(char *pipe_tab)
{
	char	**command;
	int		nb_token;

	pipe_tab = split_chevron(pipe_tab);
	nb_token = count_token(pipe_tab, ' ');
	printf("nb_token : %d\n", nb_token);
	command = NULL;
	if (!nb_token)
		return (command);
	command = ft_calloc(sizeof(char *), (nb_token + 1));
	// if (!pipe_tab)
		// return (ft_putstr_fd("error creating tab\n", 2), NULL);
	command = split_pipes(command, nb_token, pipe_tab, ' ');//) _command(command, nb_word, pipe_tab);
	return (command);
}
