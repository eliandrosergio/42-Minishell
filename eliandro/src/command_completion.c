#include "minishell.h"

// Adicione os comandos disponíveis
char *commands[] = {"cd", "exit", "help", "ls", "pwd", "echo", NULL};

// Função de completamento de comandos com correção de vazamento
char **command_completion(const char *text, int start, int end)
{
    (void)start;
    (void)end;
    return (rl_completion_matches(text, command_generator));
}

// Corrigir vazamento na geração de comandos
char *command_generator(const char *text, int state)
{
    static int  i;
    static int  len;
    char        *cmd;

    if (!state)
    {
        i = 0;
        len = strlen(text);
    }
    while ((cmd = commands[i++]))
    {
        if (strncmp(cmd, text, len) == 0)
            return (strdup(cmd)); // Alocando dinamicamente a string
    }
    return (NULL);
}
