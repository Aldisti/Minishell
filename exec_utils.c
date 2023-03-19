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
	int		len;

	if (!parsed)
		return (0);
	len = 0;
	while (parsed[len] && ft_strncmp(parsed[len], "&&", 2) && ft_strncmp(parsed[len], "||", 2))
		len++;
	cmd = (char **) malloc((len + 1) * sizeof(char *));
	cmd[len] = 0;
	if (!cmd)
		return (0);
	i = -1;
	while (++i < len)
		cmd[i] = parsed[i];
	return (cmd);
}

//	description: finds the pathname of the dir where you can find the
//	executable of the command passed in input
//	input: takes the name of the command(ls, pwd, grep, ...)
//	return: on success the pathname of the folder where you can find the
//	command(/user/bin), otherwise zero is returned
char	*ft_find_cmd(char *cmd, char **paths)
{
	char	*tmp;
	int		i;

	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		exit(write(2, "Error\nfailed to join '/' with [cmd]\n", 36) * 0 + 1);
	i = -1;
	while (paths[++i])
	{
		// printf("p: %s - cmd: %s\n", paths[i], cmd);
		tmp = ft_strjoin(paths[i], cmd);
		if (!tmp)
			return (0);
		if (!access(tmp, X_OK))
		{
			free(cmd);
			return (tmp);
		}
		free(tmp);
	}
	free(cmd);
	return (0);
}

char	*ft_execute_cmd(char **cmd)
{
	char	output[4097];
	char	*path;
	char	**env;
	int		link[2];
	int		i;

	env = ft_split(getenv("PATH"), ':');
	if (!env)
		exit(write(2, "Error\nfailed to split paths in [executor]\n", 41) * 0 + 1);
	path = ft_find_cmd(cmd[0], env);
	if (!path)
		exit(write(2, "Error\ncould not find cmd\n", 25) * 0 + 1);
	pipe(link);
	if (fork() == 0)
	{
		dup2(link[1], 1);
		close(link[0]);
		close(link[1]);
		execve(path, cmd, env);
	}
	else
	{
		close(link[1]);
		i = read(link[0], output, 4096);
		if (i < 0)
			exit(printf("Error\nread function failed\n") * 0 + 1);
		output[i] = 0;
	}
	free(cmd);
	free(path);
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	return (ft_strdup(output));
}