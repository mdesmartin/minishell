/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:23:19 by jmoutous          #+#    #+#             */
/*   Updated: 2023/06/01 14:43:57 by jmoutous         ###   ########lyon.fr   */
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
# include <sys/ioctl.h>

typedef struct s_pipeline
{
	char	**command;
	char	**redirections;
	int		here_doc_fd[2];
	int		here_doc_expand;
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
	char	**envp_tab;
	int		**pipes;
	char	*pwd;
	char	*oldpwd;
	int		nb_cmd;
	int		exit_code;
}				t_data;

//utils
void		ft_data_init(t_data *data);
void		ft_close(int fd);
void		ft_close_fds(t_data *data, int fd);
void		ft_close_hd_fds(t_data *data);
void		ft_error(t_data *data, char *s, int code);
void		ft_perror(t_data *data, char *str, int code);
void		ft_quit(t_data *data, int code);
void		ft_free_tab(char **tab);
void		ft_rfree_tab(char **tab, int i);
int			ft_is_c_in(char *str, char c);
void		ft_free_envptab(t_data *data);
void		ft_free_envplst(t_data *data);
void		ft_print_tabtab(char **tab, char *name);
char		*ft_strjoin3(char const *s1, char const *s2, char const *s3);

//env
void		ft_envp(t_data *data);
void		ft_creat_envp(t_data *data);
int			ft_check_exportvar(char *variable);
int			ft_check_exportopt(t_data *data, char *command1);
int			ft_check_unsetvar(char *variable);
int			ft_varlen(char *var);
t_envp		*ft_is_var_in_env(t_data *data, char *command);
void		ft_print_env(t_data *data);
void		ft_envadd_back(t_envp **lst, t_envp *new);
t_envp		*ft_envlast(t_envp *lst);
char		**ft_lst_to_tabtab(t_data *data, t_envp *envp);
char		**ft_split_var(t_data *data, char *var);
void		ft_update_envptab(t_data *data);
void		ft_check_hd_expand(t_pipeline *pipe, char *limiter);

//exec
void		ft_cmd(t_data *data);
int			ft_process_here_doc(t_data *data);
void		ft_child(t_data *data, int **pipes, int i);
char		*ft_get_arg_path(t_data *data, char **command);
char		*ft_getenv(t_envp *envp, char *variable);

//builtin
void		ft_export(t_data *data, char **command);
int			ft_export_append(t_data *data, char *variable);
void		ft_print_export(t_data *data);
void		ft_unset(t_data *data, char **command);
int			ft_builtin(t_data *data, char **command);
void		ft_builtin_cd(t_data *data, char **command);
void		ft_cd_home(t_data *data);
void		ft_cd_back(t_data *data);
void		ft_cd_opt(t_data *data, char *command1);
void		ft_builtin_exit(t_data *data, char **command);
void		ft_exit_redir(t_data *data, char **command, char **redirections);
void		ft_builtin_slash(t_data *data, char *directory);
int			ft_is_directory(char *directory);
void		ft_builtin_echo(t_data *data, char **command);
void		ft_check_envarg(t_data *data, char **command);

//redirection
char		**ft_redirection(t_data *data, int i);
char		**ft_extract_redirections(t_data *data,
				char **cmd, char **pipes_tab);
void		ft_apply_redirection(t_data *data, t_pipeline *pipe,
				char **redirections);
void		ft_del_redirections(char **cmd);
int			ft_ctrld_heredoc(t_data *data, char *limiter);
int			ft_ctrlc_heredoc(t_data *data, int *here_doc_fd, char *input);
char		*ft_here_doc_expand(t_data *data, t_pipeline *pipe, char *input);
void		ft_dup2_here_doc(t_data *data, t_pipeline *pipe);

//signal
void		signal_init(void (*handler)(int signum));
void		signal_handler(int signum);
void		signal_heredoc(int signum);

//parsing
int			parsing(t_data *data, char *readed);
void		expands(t_data *data, char **pipes_tab);
int			count_pipes(char *input);
char		**split_pipes(char **pipes_tab, char *input, int nb_pipes);
char		**split_tokens(t_data *data, char **pipes_tab, char *str, \
			char *charset);
void		space_chevron(t_data *data, char **pipes_tab, int nb_pipes);
void		token_parsing(char **token_tab);

//input
int			nothing_after_symbol(char *input, int i, char symbol);

//parsing_utils
int			is_whitespace(char c);
int			is_whitespace_or_end(char c);
int			is_in_quotes(char *str, int index);

//check_input
int			check_input(char *input, t_data *data);
void		print_error(char *error);
int			check_chevrons(char *input);
int			check_pipes_n_ampersand(char *input);
int			check_quotes(char *input);
int			chevron_error(char *input, int i, char chevron);

//free
void		free_lst(t_list **cmd);
void		*free_tab(char **tab);

//s_access
void		*s_init(char **content, char **redirections);
t_pipeline	*s_read_cnt(t_list *cmd);
t_pipeline	*s_convert_content(void *content);

//expands
char		*expand_handler(t_data *data, char *pipes_tab, int *start);
char		*trim_from_to(char *pipes_tab, int *start, int end);
char		*trim_by_exitcode(char *value, char *pipes_tab, int *start, \
			int end);
char		*trim_by(char *value, char *pipes_tab, int *start, int end);
int			lonely_expand_in_quote(char *str, int i, char c);

#endif