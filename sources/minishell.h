/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:19 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/16 16:21:55 by jmoutous         ###   ########lyon.fr   */
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

typedef struct s_envp
{
	char			*variable;
	char			*value;
	struct s_envp	*next;
}				t_envp;

typedef struct s_data
{
	t_list	*cmd;
	t_envp	*envp;
	int		**pipes;
	int		nb_cmd;
}				t_data;

void	ft_data_init(t_data *data);
void	ft_close_fds(t_data *data);
void	ft_error(t_data *data, char *s);
void	ft_quit(t_data *data);
void	ft_free_tab(char **tab);
int		ft_is_c_in(char *str, char c);

void	ft_cp_envp(t_data *data);
void	ft_print_env(t_data *data);
void	ft_export(t_data *data);
void	ft_envadd_back(t_envp **lst, t_envp *new);
t_envp	*ft_envlast(t_envp *lst);
void	ft_print_export(t_data *data);
char	**ft_lst_to_tabtab(t_envp *envp);

void	ft_cmd(t_data *data);
void	ft_child(t_data *data, int **pipes, int i);
char	*ft_get_arg_path(t_data *data);

int		parsing(t_data *data, char *readed);
void	*free_tab(char **tab);
void	free_lst(t_list **cmd);
void	get_signal(int signal);

#endif