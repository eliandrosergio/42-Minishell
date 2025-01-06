#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

void    minishell_loop(void);
void    parse_and_execute(char *line);
void    execute_command(char **args);
void    handle_cd(char **args);
void    handle_exit(char **args);
void    handle_pwd(void);
void    handle_echo(char **args);
void    handle_env(void);
void    handle_export(char **args);


#endif