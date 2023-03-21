/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/21 17:26:00 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dabbord checker les quotes, puis deplacer le i a la fin des quotes, ensuite split au pipe le bloc
// chaque maillon contient un pipe, chqaue str du tab est un token un pipe
// dabbord creer un tab (pipe_tab) avec a chaque str un pipe, le traiter puis ensuite a la fin split et put in chain


int find_quote(char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == quote)
			return (0);
		(*i)++;
	}
	return (ft_putstr_fd("error findding quote\n", 2), exit(1), 1);
}

int find_pipe(char *input, int *i)
{
	while (input[*i] != '\0')
	{
		if (input[*i] == '\'')
			find_quote(input, i, '\'');
		if (input[*i] == '\"')
			find_quote(input, i, '\"');
		if (input[*i] == '|')
			return (1);
		(*i)++;
	}
	return (0);
}

int	nb_pipes(char *input)
{
	int	nb_pipes;
	int	j;

	j = 0;
	nb_pipes = 1;
	while (find_pipe(input, &j))
		nb_pipes++;
	return (nb_pipes);
}

void	split_pipes(char ***pipe_tab, char *input)
{
	int start;
	int	i;
	int	j;

	start = 0;
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		find_pipe(input, &i);
		*pipe_tab[j] = ft_substr(input, start, i - start);
		j++;
		i++;
		start = i;
	}
}

void	create_tab(char ***pipe_tab, int nb_pipe)
{
	pipe_tab = ft_calloc(nb_pipe + 1, sizeof(char *));//pas sur de ca, mettre malloc ? pk +1 ?
	if (!pipe_tab)
		return (ft_putstr_fd("error creating tab\n", 2), exit(1)); 
}

void	print_tab(char **pipe_tab)
{
	int i = 0;

	while (pipe_tab[i])
	{
		ft_printf("%s\n", pipe_tab[i]);
		i++;
	}
	return ;
}

int	parsing(t_data *data, char *input)
{
	char	**pipe_tab;
	char	*inp;
	int		nb_p;

	(void) data;
	inp = ft_strdup(input);
	nb_p = nb_pipes(input);
	create_tab(&pipe_tab, nb_p);
	split_pipes(&pipe_tab, input);
	print_tab(pipe_tab);

	return (0);
}

///////////////////////////// 

void	create_chain(t_list **cmd, char **pipe)
{
	if (*cmd == NULL)
		*cmd = ft_lstnew((void**)pipe);
	else
		ft_lstadd_back(cmd, ft_lstnew((void **)pipe));
	return ;
}


// void	print_chain(t_list *cmd)
// {
// 	t_list *cp;
// 	int	i;

// 	cp = cmd;
// 	ft_putstr_fd("the command is : ", 1);
// 	while (cp)
// 	{
// 		i = 0;
// 		while (cp->content[i])
// 		{
// 			ft_printf("%s", cp->content[i]);
// 			ft_putstr_fd(" ", 1);
// 			i++;
// 		}
// 		ft_putstr_fd("| ", 1);
// 		cp = cp->next;
// 	}
// 	ft_putstr_fd("\n", 1);
// 	return ;
// }













//count nb_p token puis creer tab, remplir tab avec token, et put tab in lst






// void	divide_pipes(t_list **cmd, char *input)
// {
// 	char	**input_pipe;
// 	char	**pipe;
// 	int		i;

// 	input_pipe = ft_split(input, '|');
// 	if (!input_pipe)
// 		return (ft_putstr_fd("Error\n", 2), free(input), exit(-1));
// 	free(input);
// 	i = 0;
// 	while (input_pipe[i])
// 	{
// 		pipe = ft_split(input_pipe[i], ' ');
// 		if (!pipe)
// 			return (perror("Error\n"), free(input));
// 		create_chain(cmd, pipe);
// 		i++;
// 	}
// 	free_tab(input_pipe);
// 	return ;
// }








// most recent
// int get_start(char *input, int i, char quote)
// {
// 	while (input[i] != '\0')
// 	{
// 		if (input[i] == quote)
// 			return (i);
// 		i++;
// 	}
// 	return (error missing quote);
// }
// int get_quote(char *input, int i, char quote)
// {
// 	while (input[i] != '\0')
// 	{
// 		if (input[i] == quote)
// 			return (i);
// 		i++;
// 	}
// 	return (error missing quote);
// }

// char	*get_quote(int end, char *input, char quote)
// {
// 	int		start;
// 	char	*token;

// 	start = end;
// 	if (input[start - 1] != ' ')
// 	{
// 		while (input[start] != '\0' && input[start] != ' ')
// 			start--;
// 	}
// 	end = get_quote(input, end, quote);
// 	if (input[end + 1] != ' ')
// 	{
// 		while (input[end] != '\0' && input[end] != ' ')
// 			end++;
// 	}
// 	token = ft_substr(input, start, end - start);
// 	return (end);//need to trim all quote
// }

// //divise les tokens au sein dun pipe et renvoi 1 quans besoin diun nouveau maillon
// // 0 si fin de chaine
// void	split_token(char *input, int i)
// {

// 	char **pipe;

// 	int	token;

// 	i = 0;
// 	token = -1;
// 	while (input[i] != '\0')
// 	{
// 		while (input[i] == ' ')
// 			i++;
// 		if (input[i] == '\"')
// 			cmd[token++] = get_quote(i, input, '\"');
// 		else if (input[i] == '\'')
// 			cmd[token++] = get_quote(i, input, '\'');
// 		else if (input[i] != ' ')
// 			cmd[token++] = get_token();
// 		else if (input[i] == '|')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }


// void	create_lst(t_list **cmd, char *input)
// {
// 	char **pipe;
// 	int	i;
	
// 	pipe = 1;
// 	i = 0;
// 	while (pipe)
// 	{
// 		pipe = split_token(input, &i);
// 		if (!pipe)
// 			return (perror("Error\n"), free(input));
// 		create_chain(cmd, pipe);
// 	}
// }

// int count_token(char *input)
// {
// 	int	i;
// 	int nb_token;

// 	i = 0;
// 	nb_token = 0;
// 	while (input[i] != '\0')
// 	{
// 		if (input[i] == '\"')
// 			db++;
// 		if (input[i] == ' ' && (db % 2) == 0)
// 			nb_token++;
		

// 		while (input[i] == ' ')
// 			i++;
// 		if (input[i] == '\"')
// 			i = get_quote(input, i, '\"');
// 			nb_token++;
// 		else if (input[i] == '\'')
// 			i = get_quote(input, i, '\'');
		
// 		else if (input[i] == '|')
// 			nb_pipes++;
// 		i++;
// 	}
// 	return (nb_pipes);
// }

// }