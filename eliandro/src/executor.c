#include "minishell.h"

// Função de execução de comandos
void execute_command(char **args)
{
    if (fork() == 0)
    {
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    }
    else
    {
        wait(NULL);
    }
}
