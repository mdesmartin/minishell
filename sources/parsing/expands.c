/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:50:27 by mvogel            #+#    #+#             */
/*   Updated: 2023/05/17 15:20:10 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//must find a variable en remplace it by its value if finded, if not return -1
static char	*find_variable(t_data *data, char *pipe_tab, int *start, int end)
{
	t_envp	*cp_envp;
	int		old_size;

	cp_envp = data->envp;
	old_size = end - *start;
	while (cp_envp)
	{
		if ((ft_strncmp(cp_envp->variable, &pipe_tab[*start], old_size) == 0) \
		&& ((int)ft_strlen(cp_envp->variable) == old_size)) //si il-s sont pareils, insert
			return (cp_envp->value);
		cp_envp = cp_envp->next;
	}
	return (NULL);
}

char	*whitespace_handler(char *pipe_tab, int *start, int end)
{
	if (ft_strncmp("echo", pipe_tab, 5))
		return (pipe_tab);
	else
		return (trim_from_to(pipe_tab, start, end));
}

char	*expand_handler(t_data *data, char *pipe_tab, int *start)
{
	int	end;

	(*start)++;
	end = *start;
	if (is_whitespace_or_end(pipe_tab[*start], pipe_tab, *start)) //rajouter ici, check if echo in pipe and if just trim $
		return (whitespace_handler(pipe_tab, start, end));
	else if (pipe_tab[*start] == '?')
		return (trim_by_exitcode(ft_itoa((int)data->exit_code), pipe_tab, start, end));
	else if (ft_isdigit(pipe_tab[*start])) 
		return (trim_from_to(pipe_tab, start, end + 1));
	else
	{
		while (ft_isalnum(pipe_tab[end]) || pipe_tab[end] == '_') // !is_whitespace_or_end(pipe_tab[end])) //|| pipe_tab[end] != '\"'?
			end++;
		if (find_variable(data, pipe_tab, start, end))
			return (trim_by(find_variable(data, pipe_tab, start, end), \
			pipe_tab, start, end));
		else
			return(trim_from_to(pipe_tab, start, end)); //remplace $ par et ce qui suit par rien
	}
	return (pipe_tab);
}

char*	expand_by_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_quotes(line, i))
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '$')
		{
			line = expand_handler(data, line, &i);
			if (!line)
				return (NULL);
		}
		if (line[i])
			i++;	
	}
	return (line);
}

void	expands(t_data *data, char **pipe_tab)
{
	int	j;

	j = 0;
	while (pipe_tab[j])
	{
		pipe_tab[j] = expand_by_line(data, pipe_tab[j]);
		if (!pipe_tab)
			return (free_tab(pipe_tab), ft_quit(data, 12));
		j++;
	}
	return ;
}
