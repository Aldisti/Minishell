#include "minishell.h"

int	main(void)
{
	char	*line;
	char	*tmp;

	while (42)
	{
		line = readline("$> ");
		add_history(line);
		if (!strncmp(line, "cd", 2))
			chdir(line + 3);
		else if (!strcmp(line, "pwd"))
		{
			tmp = getcwd(0, 0);
			printf("%s\n", tmp);
			free(tmp);
		}
		else if (!strcmp(line, "exit"))
		{
			rl_clear_history();
			free(line);
			break ;
		}
		free(line);
	}
	return (0);
}
