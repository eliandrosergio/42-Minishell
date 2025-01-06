#include "minishell.h"

// Função de parsing e execução de comandos
void parse_and_execute(char *line)
{
    char *args[1000];
    int i = 0;
    char *token;

    token = strtok(line, " \n");
    while (token)
    {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
    // Executa o comando
    execute_command(args);
}
