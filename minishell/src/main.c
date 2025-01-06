#include "minishell.h"

int	main(int ac, char **av)
{
	if (ac > 1)
	{
		if (strcmp(av[0], "PATH") == 0)
		{
			printf("testando\n");
			return (0);
		}
	}
	minishell_loop();
	return (0);
}
