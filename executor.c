#include "minishell.h"

//	description: gets all "tokens" before the first "&&" or "||"
//	input: array of pointers to strings
//	like ["pwd", "&&", "ls", "-a", "dir"]
//	output: returns an array of pointers to all the strings
//	before the first "&&" or "||" or EOF
char	**ft_getcmd(char **parsed)
{
	char	**cmd;
	int		i;

	if (!parsed)
		return (0);
	i = 0;
	while (parsed[i] && strcmp(parsed[i], "&&") && strcmp(parsed[i], "||"))
		i++;
	cmd = (char **) ft_calloc(i, sizeof(char *));
	if (!cmd)
		return (0);
	while (--i >= 0)
		cmd[i] = parsed[i];
	return (cmd);
}

//	description: finds the pathname of the dir where you can find the
//	executable of the command passed in input
//	input: takes the name of the command(ls, pwd, grep, ...)
//	return: on success the pathname of the folder where you can find the
//	command(/user/bin), otherwise zero is returned
char	*ft_find_cmd(const char *cmd)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_slpit(getenv("PATH"), ':');
	if (!paths)
		return (0);
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		return (0);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], cmd);
		if (!tmp)
			return (0);
		if (!access(tmp, X_OK))
		{
			free(tmp);
			free(cmd);
			return (paths[i]);
		}
		free(tmp);
	}
	free(cmd);
	return (0);
}

char	*ft_executor(char **cmd)
{
	char	*output;
	int		i;
	int		j;

	i = 0;
	free(cmd);
	return (output);
}