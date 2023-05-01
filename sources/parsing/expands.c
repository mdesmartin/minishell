/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:50:27 by mvogel            #+#    #+#             */
/*   Updated: 2023/05/01 22:56:42 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//trim a str of a str
char	*trim_from_to(char *pipe_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		i;

	i = 0;
	new_size = ft_strlen(pipe_tab) - (end - *start);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	while (i < *start - 1)
	{
		new_content[i] = pipe_tab[i];
		i++;
	}
	while (pipe_tab[end])
		new_content[i++] = pipe_tab[end++];
	*start = 0;
	return (new_content);
}

char	*trim_by(char *value, char *pipe_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		old_size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	old_size = end - *start;
	new_size = ft_strlen(pipe_tab) - old_size + ft_strlen(value);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	while (i < *start - 1)
	{
		new_content[i] = pipe_tab[i];
		i++;
	}
	while (value[j])
		new_content[i++] = value[j++];
	while (pipe_tab[end])
		new_content[i++] = pipe_tab[end++];
	*start = 0;
	return (new_content);
}

//must find a variable en remplace it by its value if finded, if not return -1
char	*find_variable(t_data *data, char *pipe_tab, int *start, int end)
{
	t_envp	*cp_envp;
	int		old_size = end - *start;

	// printf("oldsize:%d\n", old_size);
	cp_envp = data->envp;
	while (cp_envp)
	{
		if ((ft_strncmp(cp_envp->variable, &pipe_tab[*start], old_size) == 0) && ((int)ft_strlen(cp_envp->variable) == old_size))//si il-s sont pareils, insert
			return (cp_envp->value);
		cp_envp = cp_envp->next;
	}
	return (NULL);
}


char	*expand_handler(t_data *data, char *pipe_tab, int *start)
{
	int	end;
	int expand;
	
	expand = *start;
	(*start)++;
	end = *start;
	(void) expand;
	if (is_whitespace_or_end(pipe_tab[*start]))
		return(trim_from_to(pipe_tab, start, end));
	// else if (pipe_tab[*start] == '?')
	// 	return(trim_by(ft_itoa((int)g_exitcode), pipe_tab, start, end));
	else
	{
		while (!is_whitespace_or_end(pipe_tab[end]))//|| pipe_tab[end] != '\"'?
			end++;
		if (find_variable(data, pipe_tab, start, end))
			return (trim_by(find_variable(data, pipe_tab, start, end), pipe_tab, start, end));
		else
			return(trim_from_to(pipe_tab, start, end));//remplace $ par et ce qui suit par rien
	}
	return (pipe_tab);
}

void	expands(t_data *data, char **pipe_tab)
{
	int		i;
	int		j;

	j = 0;
	while (pipe_tab[j])
	{
		i = 0;
		while (pipe_tab[j][i])
		{
			if (pipe_tab[j][i] == '\'' && !in_quotes(pipe_tab[j], i))
			{
				i++;
				while (pipe_tab[j][i] != '\'')
					i++;
			}
			else if (pipe_tab[j][i] == '$')
				pipe_tab[j] = expand_handler(data, pipe_tab[j], &i);// à free ?
			i++;
		}
		j++;
	}
	return ;
}
