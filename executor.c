#include "minishell.h"

int	ft_executor(char **parsed)
{
	char	*output;
	char	**full_cmd;
	int		i;
	int		pipes;

	full_cmd = ft_getcmd(parsed);
	if (!full_cmd)
		exit(write(2, "Error\n[ft_getcmd] failed\n", 25) * 0 + 1);
	i = -1;
	pipes = 0;
	while (full_cmd[++i])
		if (!ft_strncmp(full_cmd[i], "|", 1))
			full_cmd[i] = 0;
	output = ft_execute_cmd(full_cmd);
	printf("%s\n", output);
	i = 0;
	while (parsed[i])
		free(parsed[i++]);
	free(parsed);
	free(output);
	return (1);
}