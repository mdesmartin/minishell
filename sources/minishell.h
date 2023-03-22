/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:19 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/22 15:41:26 by mvogel           ###   ########lyon.fr   */
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
# include <signal.h>

typedef struct s_data
{
	t_list	*cmd;
	char	**envp;
	int		**pipes;
	int		nb_cmd;
}				t_data;

void	ft_data_init(t_data *data, char **envp);
void	ft_close_fds(t_data *data);
void	ft_error(t_data *data, char *s);
void	ft_quit(t_data *data);
void	ft_free_tab(char **tab);

void	ft_cmd(t_data *data);
void	ft_child(t_data *data, int **pipes, int i);
char	*ft_get_arg_path(t_data *data);

int		parsing(t_data *data, char *readed);
void	*free_tab(char **tab);
void	free_lst(t_list **cmd);
void	get_signal(int signal);
int		nb_pipes(char *input);
char	**create_tab(char **pipe_tab, char *input, int nb_pipe);

#endif