#include "minishell.h"

int	shell_errno = 0;

char	*ft_resolve_expansion(t_env env, char *str)
{
	char	*expansion;

	if (!str || !*str)
		return (ft_strdup("$"));
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_itoa(shell_errno));
	while (env.next && ft_strncmp(env.name, str, ft_strlen(str)))
		env = *(env.next);
	if (!ft_strncmp(env.name, str, ft_strlen(str)))
	{
		free(str);
		return (ft_strdup(env.value));
	}
	expansion = getenv(str);
	free(str);
	return (expansion);
}

int	ft_check_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && (str[i + 1] != 32 && str[i + 1]))
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
		expansion = ft_resolve_expansion(*(shell->env), ft_substr(dollar, 1, i - 1));
		// free(str);
		dollar = ft_strjoin(left, expansion);
		str = ft_strjoin(dollar, right);
		free(left);
		free(right);
		// free(dollar);
		// printf("|%s|\n", str);
	}
	return (str);
}

int	main(void)
{
	t_shell	shell;
	t_env	env;
	char	*str;

	shell.env = &env;
	env.name = "HOME";
	env.value = "CIAO";
	env.next = 0;
	printf("\n%s\n", ft_expansion(&shell, "ls -a $ HOME $USERNAME$HOME $? "));
}