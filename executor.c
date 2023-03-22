#include "minishell.h"

int	shell_errno = 169;

char	*ft_resolve_expansion(t_env *env, char *str)
{
	char	*expansion;

	if (!str || !*str)
		return (ft_strdup("$"));
	if (!ft_strncmp(str, "$", ft_strlen(str)))
		return (ft_strdup(""));
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_itoa(shell_errno));
	while (env && env->name && ft_strncmp(env->name, str, ft_strlen(str)))
		env = env->next;
	if (env && env->name && !ft_strncmp(env->name, str, ft_strlen(str)))
		expansion = ft_strdup(env->value);
	else
		expansion = getenv(str);
	free(str);
	if (!expansion)
		return (ft_strdup(""));
	return (expansion);
}

int	ft_check_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i + 1] && str[i] == '$' && str[i + 1] != 32)
			return (i);
	return (-1);
}

char	*ft_expansion(t_shell *shell, char *str)
{
	int		i;
	char	*left;
	char	*right;
	char	*dollar;
	char	*expansion;

	while (ft_check_dollar(str) != -1)
	{
		dollar = str + ft_check_dollar(str);
		i = 1;
		while (dollar[i] && dollar[i] != '$' && dollar[i] != 32)
			i++;
		left = ft_substr(str, 0, dollar - str);
		right = ft_substr(dollar, i, ft_strlen(dollar) - i + 1);
		expansion = ft_resolve_expansion(shell->env, ft_substr(dollar, 1, i - 1));
		free(str);
		dollar = ft_strjoin(left, expansion);
		str = ft_strjoin(dollar, right);
		if (left)
			free(left);
		if (right)
			free(right);
		if (dollar)
			free(dollar);
	}
	return (str);
}

int	main(void)
{
	t_shell	shell;
	t_env	env;
	t_env	env2;
	char	*str;

	shell.env = &env;
	env.name = "HOME";
	env.value = "GPANICO";
	env.next = &env2;
	env2.name = "USERNAME";
	env2.value = "AFRACCAL";
	env2.next = 0;
	printf("\n<%s>\n", ft_expansion(&shell, "$HOME $!"));
}