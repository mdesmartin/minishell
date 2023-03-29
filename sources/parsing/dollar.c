/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:50:27 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/29 16:29:55 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//trim a str of a str
void	trim_from_to(t_data *data, int start, int end)
{
	char	**new_content;
	int		new_size;
	int		i;

	new_size = ft_strlen(s_access_content(data->cmd)->command[0]) - (end - start);
	new_content = ft_calloc(sizeof(char *), 2);
	new_content[0] = ft_calloc(sizeof(char), new_size);
	i = 0;
	while (i++ < start)
		new_content[0][i] = s_access_content(data->cmd)->command[0][i];
	while (s_access_content(data->cmd)->command[0][end])
		new_content[0][i++] = s_access_content(data->cmd)->command[0][end++];
	return ;
}

//must find a variable en remplace it by its value if finded, if not return -1
int	find_variable(t_data *data, int start, int end, int size)
{
	t_envp	*cp;
	char	**new_content;
	int		new_size;
	int		i;
	int		j;

	cp = data->envp;
	new_size = 0;
	while (cp)
	{
		i = 0;
		j = 0;
		if (!ft_strncmp(cp->variable, s_access_content(data->cmd)->command[0] - start, size))//si ils sont pareils, insert
		{
			new_size = ft_strlen(s_access_content(data->cmd)->command[0]) - size + ft_strlen(cp->value);
			new_content = ft_calloc(sizeof(char *), 2);
			new_content[0] = ft_calloc(sizeof(char), new_size + 1);
			while (i++ < start)
				new_content[0][i] = s_access_content(data->cmd)->command[0][i];
			while (cp->value[j])
				new_content[0][i++] = cp->value[j++];
			while (s_access_content(data->cmd)->command[0][end])
				new_content[0][i++] = s_access_content(data->cmd)->command[0][end++];
			i++;
			new_content[i] = '\0';
			s_replace_command(data, new_content);//// NEED TO MODIFYYYYY /!\  /
			return (0);
		}
		cp = cp->next;
	}
	return (-1);
}

void	dollar_handler(t_data *data, int start)
{
	int	end;

	end = start;
	if (s_access_content(data->cmd)->command[0][start] == '\0' \
	|| s_access_content(data->cmd)->command[0][start] == ' ')
		return ;
	// else if (data->cmd->content[0][start] == '?')
		//remplace $ by exitcode
	else
	{
		while (ft_isalpha(s_access_content(data->cmd)->command[0][end]))
			end++;
		if (find_variable(data, start, end, end - start) == -1)
			trim_from_to(data, start, end);//remplace $ par et ce qui suit par rien
	}
	return ;
}

void	dollar(t_data *data)
{
	int		i;

	while (data->cmd)
	{
		i = 0;
		while (s_access_content(data->cmd)->command[0][i])
		{
			if (s_access_content(data->cmd)->command[0][i] == '\'')
			{
				while (s_access_content(data->cmd)->command[0][i] != '\'')
					i++;
			}
			else if (s_access_content(data->cmd)->command[0][i] == '$')
			{
				i++;
				dollar_handler(data, i);
			}
			i++;
		}
		data->cmd = data->cmd->next;
	}
	return ;
}