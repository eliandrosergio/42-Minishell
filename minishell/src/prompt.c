/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonfer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 08:30:43 by antonfer          #+#    #+#             */
/*   Updated: 2024/11/27 08:33:33 by antonfer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_loop(void)
{
    char *line = NULL;
    size_t len = 0;

    while (1)
    {
        printf("minishell> "); // Prompt
        if (getline(&line, &len, stdin) == -1) // Leitura
        {
            printf("exit\n");
            break;
        }
        if (strcmp(line, "\n") != 0) // Ignorar linhas vazias
        {
            parse_and_execute(line);
        }
    }
    free(line);
}