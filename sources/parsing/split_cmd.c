/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:06:52 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/04/12 15:26:02 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// do split with spaces, implant before and after word whiler space, then chevron should be serounded by spaces
// fisrt transform sentence by adding spacesd betwen chevron when it should be there, then split spaces,
//pb many spaces, wrong count only here

//work: split before and after < > << >> or " " or "	"

// void	is_double(char *input, int *i, char c)
// {
// 	while (input[*i] != '\0')
// 	{
// 		(*i)++;
// 		if (input[*i] == c)
// 			return ;
// 		else
// 		{
// 			(*i)--;
// 			return ;
// 		}
// 	}
// }

// int	find_separator(char *input, int *i)
// {
// 	while (input[*i] != '\0')
// 	{
// 		if (input[*i] == '\'')
// 			find_quote(input, i, '\'');
// 		if (input[*i] == '\"')
// 			find_quote(input, i, '\"');
// 		if (input[*i] == ' ' || input[*i] == '	')
// 			return (-1);
// 		if (input[*i] == '>')
// 			return (is_double(input, i, '>'), 1);
// 		if (input[*i] == '<')
// 			return (is_double(input, i, '<'), 1);//?non
// 		(*i)++;
// 	}
// 	return (0);
// }

// static int	ft_numb_word(char const *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s && *s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s)
// 			i++;
// 		while (*s != c && *s)
// 			s++;
// 	}
// 	return (i);
// }


// int	count_word(char *input)
// {
// 	int	nb_word;
// 	int	j;
// 	int	n;

// 	nb_word = 0;
// 	j = 0;
// 	n = 1;
// 	while (n)
// 	{
// 		n = find_separator(input, &j, ' ');
// 		// if (n == 1 && (input[j - 1] != ' ' || input[j - 1] != '	'))
// 		// 	nb_word += 2;
// 		// else
// 		nb_word += 1;
// 		j++;
// 	}
// 	return (nb_word);
// }

// ok lol<<mwhsi


// char	**split_command(char **command, int nb_word, char *pipe_tab)
// {
// 	int	start;
// 	int	len_command;
// 	int	i;
// 	int	j;

// 	start = 0;
// 	len_command = 0;
// 	i = 0;
// 	j = 0;
// 	while (nb_word)
// 	{
// 		find_separator(pipe_tab, &i, ' ');
// 		len_command = i - start;
// 		command[j] = ft_substr(pipe_tab, start, len_command);
// 		// if (!command[j])
// 			// return (ft_putstr_fd("error creating tab\n", 2), NULL);
		
// 		j++;
// 		i++;
// 		start = i;
// 		nb_word--;
// 	}
// 	command[j] = NULL;
// 	return (command);
// }


// int	count_chevron(char *str)
// {
// 	int	chevron;

// 	chevron = 0;
// 	while (*str)
// 	{
// 		if (*str == '>')
// 		{
// 			str++;
// 			if (*str == '>')
// 				str++;
// 			chevron++;
// 		}
// 		else if (*str == '<')
// 		{
// 			str++;
// 			if (*str == '<')
// 				str++;
// 			chevron++;
// 		}
// 		else
// 			str++;
// 	}
// 	return (chevron);
// }

// int	count_chevron(char *input)
// {
// 	int	nb_chevron;
// 	int	i;

// 	i = 0;
// 	nb_chevron = 0;
// 	while (input && input[i])
// 	{
// 		// while (input[i] == separator)
// 		// 	i++;
// 		if (input[i])
// 			nb_chevron++;
// 		while (input[i] != '<' && input[i])
// 		{
// 			if (input[i] == '\'')
// 				find_quote(input, &i, '\'');
// 			if (input[i] == '\"')
// 				find_quote(input, &i, '\"');
// 			i++;
// 		}
// 	}
// 	return (nb_chevron);
// }

void	skip_quote(char *input, int *i)
{
	if (input[*i] == '\'')
		find_quote(input, i, '\'');
	if (input[*i] == '\"')
		find_quote(input, i, '\"');
	return ;
}

int	need_space(char *str, int *i)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		i++;
		if (str[*i] == '>' || str[*i] == '<')
			return (1);
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

	int len = ft_strlen(str);

	printf("len_str : %d\n", len);
	new = ft_calloc((ft_strlen(str)) * 2, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		skip_quote(str, &i);
		if (need_space(str, &i))
			new[j] = ' ';
		else
			new[j] = str[i];
		j++;
		i++;
	}
	printf("s_chv : %s\n", new);
	free(str);
	return (new);
}

int	count_token(char *input, char separator)
{
	int	nb_token;
	int	i;

	i = 0;
	nb_token = 0;
	while (input && input[i])
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
	nb_token = count_token(pipe_tab, ' ');// count_word(pipe_tab);
	printf("nb_token : %d\n", nb_token);
	command = NULL;
	command = ft_calloc(sizeof(char *), (nb_token + 1));
	// if (!pipe_tab)
		// return (ft_putstr_fd("error creating tab\n", 2), NULL);
	command = split_pipes(command, nb_token, pipe_tab, ' ');//) _command(command, nb_word, pipe_tab);
	return (command);
}
