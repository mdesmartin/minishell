/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:19 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/08 14:14:35 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/sources/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	char	**envp;
	int		**pipes;
	int		nb_cmd;
}				t_data;

void	ft_data_init(t_data *data);
void	ft_close_fds(t_data *data);
void	ft_error(t_data *data, char *s);
void	ft_quit(t_data *data);
void	ft_free_tab(char **tab);

void	ft_process(t_data *data);
void	ft_child(t_data *data, int **pipes, int i);
char	*ft_get_arg_path(t_data *data);

#endif