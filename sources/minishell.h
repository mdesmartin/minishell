/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:19 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/29 16:29:33 by mehdidesmar      ###   ########lyon.fr   */
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

// input[0] : 0 = < ; 1 = <<
// input[1] : file or limiter
// output[0] : 0 = > ; 1 = >>
// output[1] : file if output[0] == 0
typedef struct s_pipeline
{
	char			**command;
	char			**input;
	char			**output;
}					t_pipeline;

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
int		nb_pipes(char *input);
char	**create_tab(char **pipe_tab, char *input, int nb_pipe);

int	split_pipes(t_data *data, int nb_p, char *input);
void	create_chain(t_list **cmd, void *content);
t_pipeline	*s_convert_content(void *content);
t_pipeline	*s_access_content(t_list *cmd);
void	dollar(t_data *data);
void	s_replace_command(t_data *data, char **new_command);

#endif