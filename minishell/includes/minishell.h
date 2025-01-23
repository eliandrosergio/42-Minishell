/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/22 16:27:00 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

# ifndef PROMPT
#  define PROMPT "minishell$ "
# endif

# ifndef CMD_BUFFER
#  define CMD_BUFFER 131072
# endif

# ifndef EXEC
#  define EXEC 1
# endif

# ifndef REDIR
#  define REDIR 2
# endif

# ifndef PIPE
#  define PIPE 3
# endif

typedef struct s_fd
{
	int				fd_in;
	int				fd_out;
	int				fd_heredoc;
	char			*filename_in;
	char			*filename_out;
}					t_fd;

typedef struct s_env
{
	char			*key;
	int				equal;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				argc;
	int				type;
	t_fd			fd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	t_cmd			*cmd;
	t_env			*envp_list;
	char			**cmdstmp;
	char			*line;
	char			**envp;
	int				status;
	int				heredoc_exitstatus;
	int				pipe_fd[2];
}					t_shell;

char				**ft_matdup(char **mat);
char				*ft_limit_buffer(char *line);

void				free_cmd(t_cmd **cmd);
void				ft_free_args(char **args);
int					ft_free_all(t_shell *shell, int flag, int ret_stat);
void				ft_free_envp_list(t_env *env);

t_shell				*ft_shell_address(t_shell *shell);
void				ft_signal_handler(int signum);
void				ft_init_shell(t_shell *shell, char **envp);
t_fd				*ft_fd_address(t_fd *fd);
int					ft_crtl_c(int value);

int					ft_exit_atol(char *str);
int					ft_lstsize_cmd(t_cmd *lst);
int					ft_chrcmpstr(char chr, char *str);
int					ft_skiptochr(char *line, int i, char chr);

void				ft_handle_ispipe(t_cmd *new, int is_pipe);
char				*ft_limit_buffer(char *line);
char				**ft_parser_split(char *line, char *delim);
int					ft_is_pipe(char *line);
int					ft_check_unvalid(char *line);

int					toggle_quotes(int quotes);
bool				handle_pipe(int *token);
bool				handle_redirection(int *token, char *line, int *i);
bool				handle_less_than(int *token, char *line, int *i);
bool				handle_other_chars(char ch, int *token);

void				add_args_and_output(t_cmd *new, char **args, t_fd *fds);
void				add_cmd(t_shell *shell, char **args, t_fd *fds,
						int is_pipe);
void				parse_line(t_shell *shell);

void				ft_init_fd(t_fd *fds);
void				ft_reset_fd_out(t_fd *fds);
void				ft_reset_fd_in(t_fd *fds);
void				ft_reset_fd(t_fd *fds);

void				ft_heredoc_handler(t_fd *fds, t_shell *shell);

int					ft_strlen_meta(char *str);
char				*ft_strchrstr(char *str, char *to_find);
char				*ft_strchr_dupfilename(char *line, int i, t_shell *shell,
						int expand);

void				ft_open_file(char *line, int i, t_fd *fds, t_shell *shell);
void				ft_parse_redir_and_set_fd(char *line, t_fd *fds,
						t_shell *shell);

bool				ft_is_end_of_var(char *matrix, int block_flag,
						int inside_quotes, int j);
void				ft_quotes_block_toggle(char c, int *block_flag,
						int *inside_quotes);
void				ft_switch_flags(int *block_flag);
void				ft_expand_sign_matrix(char **matrix, t_shell *shell, int i);
int					ft_deal_with_quotes(char **matrix, int i, int j,
						t_shell *shell);
void				ft_remove_quotes_logic(char *str, int len);
char				*ft_putstr_instr(char *str, char *insert_str,
						int insert_len, int insert_index);
char				*ft_strchr_validenv(const char *s);

t_env				*ft_get_envp_list(char **envp);
t_env				*ft_dupenv(t_env *env);
t_env				*ft_lstlast_envp(t_env *lst);
void				ft_sort_env(t_env *env);
void				ft_update_envp_matrix(t_shell *shell);
char				*ft_getenv(char *key, t_env **envp_list);
int					ft_lstsize_envp(t_env *lst);

void				ft_export_new_key(char *arg, t_shell *shell);
int					ft_export_on_same_key(char *arg, t_shell *shell);
int					ft_invalid_key(char *str);

int					ft_exit(t_shell *shell, int flag);
int					ft_cd(t_cmd *cmd, t_shell *shell);
int					ft_pwd(void);
int					ft_export(t_cmd *cmd, t_shell *shell);
int					ft_unset(t_cmd *cmd, t_shell *shell);
int					ft_env(t_shell *shell);
bool				is_n_flag(const char *arg);
int					ft_echo(t_cmd *cmd);

void				ft_execve(char *bin, char **args, char **env,
						t_shell *shell);
void				ft_dup2(int fd, int fd2, t_shell *shell, char *bin_route);
void				ft_signal_hand(int signum);
pid_t				ft_fork(t_shell *shell);

void				ft_exec_on_path(t_shell *shell, t_cmd *cmd);
char				*ft_get_bin_based_on_path(char *bin_route, t_shell *shell,
						t_cmd *cmd);
int					ft_exec_on_builtin(t_cmd *cmd, t_shell *shell);
int					ft_exec_on_parent(t_cmd *cmd, t_shell *shell);

void				exec_cmd(t_shell *shell);

#endif
