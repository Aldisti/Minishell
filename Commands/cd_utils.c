#include "../minishell.h"

int	ft_die_cd(char *trueold, char *oldpwd, char *cmd, int ret)
{
	if (trueold)
		fd_printf(2, "Minishell: cd: %s: ", trueold);
	else
		fd_printf(2, "Minishell: cd: %s: ", cmd);
	write(2, "\033[31m", 5);
	perror("");
	write(2, "\033[0m", 4);
	ft_free((void **) &oldpwd);
	return (ret);
}

void	ft_update_error(t_shell *shell, char *cmd, int lvl)
{
	t_env	*env;
	char 	*tmp;

	write(2, "\033[31m", 5);
	write(2, "cd: error retrieving current directory:", 39);
	write(2, " getcwd: cannot access parent directories", 41);
	perror("");
	write(2, "\033[0m", 4);
	env = ft_get_env(ft_get_node(shell->list, "PWD"), lvl);
	if (!cmd[1])
		tmp = ft_strjoin(env->value, "/.");
	else
		tmp = ft_strjoin(env->value, "/..");
	if (!tmp)
		ft_die(shell, 1, 12);
	ft_free((void **) &env->value);
	env->value = tmp;
}

void	ft_update_pwd(t_shell *shell, char *cmd, int lvl)
{
	char	*pwd;
	t_env	*env;

	errno = 0;
	pwd = getcwd(0, 0);
	if (!pwd && errno == 2)
	{
		ft_update_error(shell, cmd, lvl);
		return ;
	}
	else if (!pwd)
		ft_die(shell, 1, 12);
	env = ft_get_env(ft_get_node(shell->list, "PWD"), lvl);
	ft_free((void **) &env->value);
	env->value = pwd;
}
