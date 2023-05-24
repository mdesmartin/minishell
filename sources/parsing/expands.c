/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expands.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:50:27 by mvogel            #+#    #+#             */
/*   Updated: 2023/05/24 13:28:39 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_variable(t_data *data, char *pipes_tab, int *start, int end)
{
	t_envp	*cp_envp;
	int		old_size;

	cp_envp = data->envp;
	old_size = end - *start;
	while (cp_envp)
	{
		if ((ft_strncmp(cp_envp->variable, &pipes_tab[*start], old_size) == 0) \
		&& ((int)ft_strlen(cp_envp->variable) == old_size))
			return (cp_envp->value);
		cp_envp = cp_envp->next;
	}
	return (NULL);
}

char	*whitespace_handler(char *pipes_tab, int *start, int end)
{
	if (ft_strncmp("echo", pipes_tab, 5))
		return (pipes_tab);
	else
		return (trim_from_to(pipes_tab, start, end));
}

char	*expand_handler(t_data *data, char *pipes_tab, int *start)
{
	int	end;

	(*start)++;
	end = *start;
	if (pipes_tab[*start] == ':' || pipes_tab[*start] == '=')
		return (pipes_tab);
	else if (is_whitespace_or_end(pipes_tab[*start], pipes_tab, *start))
		return (whitespace_handler(pipes_tab, start, end));
	else if (pipes_tab[*start] == '?')
		return (trim_by_exitcode(ft_itoa((int)data->exit_code), \
		pipes_tab, start, end));
	else if (ft_isdigit(pipes_tab[*start]))
		return (trim_from_to(pipes_tab, start, end + 1));
	else
	{
		while (ft_isalnum(pipes_tab[end]) || pipes_tab[end] == '_')
			end++;
		if (find_variable(data, pipes_tab, start, end))
			return (trim_by(find_variable(data, pipes_tab, start, end), \
			pipes_tab, start, end));
		else
			return (trim_from_to(pipes_tab, start, end));
	}
	return (pipes_tab);
}

char	*expand_by_line(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !is_in_quotes(line, i))
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '$' && !ft_strnstr(line, "<<", ft_strlen(line)))
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

void	expands(t_data *data, char **pipes_tab)
{
	int	j;

	j = 0;
	while (pipes_tab[j])
	{
		pipes_tab[j] = expand_by_line(data, pipes_tab[j]);
		if (!pipes_tab)
			return (free_tab(pipes_tab), ft_quit(data, 12));
		j++;
	}
	return ;
}
