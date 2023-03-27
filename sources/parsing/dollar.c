/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:50:27 by mvogel            #+#    #+#             */
/*   Updated: 2023/03/27 17:05:36 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar(t_data *data)
{
	int		i;

	while (data->cmd)
	{
		i = 0;
		while (data->cmd->content[0][i])
		{
			if (data->cmd->content[0][i] == '\'')
			{
				while (data->cmd->content[0][i] != '\'')
					i++;
			}
			else if (data->cmd->content[0][i] == '$')
				dollar_handler(data, i);
			i++;
		}
		data->cmd = data->cmd->next;
	}
	return ;
}

void	dollar_handler(t_data *data, int start)
{
	int	end;

	end = start;
	if (data->cmd->content[0][start] == '\0' || data->cmd->content[0][start] == ' ')
		return ;
	// else if (data->cmd->content[0][start] == '?')
		//remplace $ by exitcode
	else
	{
		while (ft_isalpha(data->cmd->content[0][end]))
			end++;
		if (find_variable(data, start, end, end - start) == -1)
			trim_from_to(data, start, end);//remplace $ par et ce qui suit par rien
	}
	return ;
}

//must find a variable en remplace it by its value if finded, if not return -1

int	find_variable(t_data *data, int start, int end, int size)
{
	t_envp	*cp;
	char	**new_content;
	int		new_size;
	int		i;

	cp = data->envp;
	new_size = 0;
	i = 0;
	while (cp)
	{
		if (!ft_strncmp(cp->variable, data->cmd->content[0] - start, size))//si ils sont pareils
		{
			new_size = ft_strlen(data->cmd->content[0]) - size + ft_strlen(cp->value);
			new_content = ft_calloc(sizeof(char *), 2);
			new_content[0] = ft_calloc(sizeof(char), new_size);
			while (i++ < start)
				new_content[i] = data->cmd->content[0][i];
			while (cp->value[j])
				new_content[i++] = cp->value[j++];
			while (data->cmd->content[0][end])
				new_content[i++] = data->cmd->content[0][end++];
			//new_content[i] = '\0';
			data->cmd->content = new_content;
			return (0);
		}
		cp = cp->next;
	}
	return (-1);
}

//trim a str of a str

void	trim_from_to(t_data *data, int start, int end, char c)
{
	char	**new_content;
	int		new_size;
	int		i;

	new_size = ft_strlen(data->cmd->content[0]) - (end - start);
	new_content = ft_calloc(sizeof(char *), 2);
	new_content[0] = ft_calloc(sizeof(char), new_size);
	i = 0;
	while (i++ < start)
		new_content[i] = data->cmd->content[0][i];
	while (data->cmd->content[0][end])
		new_content[i++] = data->cmd->content[0][end++];
	return ;
}

//14h continue ths way with memcpymaybe, but using list instead of char**
