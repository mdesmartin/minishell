/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:50:27 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/30 12:25:17 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//trim a str of a str
char	*trim_from_to(char *pipe_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		i;

	new_size = ft_strlen(pipe_tab) - (end - *start);
	new_content = ft_calloc(sizeof(char), new_size);
	i = 0;
	while (i++ < *start)
		new_content[i] = pipe_tab[i];
	while (pipe_tab[end])
		new_content[i++] = pipe_tab[end++];
	*start = i;
	new_content[i] = '\0';
	return (new_content);
}

char	*trim_by(char *value, char *pipe_tab, int *start, int end)
{
	char	*new_content;
	int		new_size;
	int		old_size = end - *start;
	int		i;
	int		j;

	new_size = 0;
	i = 0;
	j = 0;
	new_size = ft_strlen(pipe_tab) - old_size + ft_strlen(value);
	new_content = ft_calloc(sizeof(char *), 2);
	new_content = ft_calloc(sizeof(char), new_size + 1);
	while (i++ < *start)
		new_content[i] = pipe_tab[i];
	while (value[j])
		new_content[i++] = value[j++];
	*start = i;
	while (pipe_tab[end])
		new_content[i++] = pipe_tab[end++];
	i++;
	new_content[i] = '\0';
	return (new_content);
}

//must find a variable en remplace it by its value if finded, if not return -1
char	*find_variable(t_data *data, char *pipe_tab, int *start, int end)
{
	t_envp	*cp_envp;
	int		old_size = end - *start;

	cp_envp = data->envp;
	while (cp_envp)
	{
		if (!ft_strncmp(cp_envp->variable, pipe_tab - *start, old_size))//si ils sont pareils, insert
			return (cp_envp->value);
		cp_envp = cp_envp->next;
	}
	return (NULL);
}

char	*dollar_handler(t_data *data, char *pipe_tab, int *start)
{
	int	end;

	end = *start;
	if (pipe_tab[*start] == '\0' || pipe_tab[*start] == ' ')
		return (pipe_tab);
	// else if (pipe_tab[start] == '?')
		//remplace $ by exitcode
	else
	{
		while (ft_isalpha(pipe_tab[end]))
			end++;
		if (find_variable(data, pipe_tab, start, end))
			return (trim_by(find_variable(data, pipe_tab, start, end), pipe_tab, start, end));
		else
			return(trim_from_to(pipe_tab, start, end));//remplace $ par et ce qui suit par rien
	}
	return (pipe_tab);
}

void	dollar(t_data *data, char **pipe_tab)
{
	int		i;
	int		j;

	j = 0;
	while (pipe_tab[j])
	{
		i = 0;
		while (pipe_tab[j][i])
		{
			if (pipe_tab[j][i] == '\'')
			{
				while (pipe_tab[j][i] != '\'')
					i++;
			}
			else if (pipe_tab[j][i] == '$')
			{
				i++;
				pipe_tab[j] = dollar_handler(data, pipe_tab[j], &i); // partir sur cette idee jeudi, a free
			}
			i++;
		}
		j++;
	}
	return ;
}
