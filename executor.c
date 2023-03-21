#include "minishell.h"

int	shell_errno = 0;

char	*ft_resolve_expansion(t_env *env, char *str)
{
	char	*expansion;
	t_env	*tmp;

	printf("resolve: |%s|\n", str);
	if (!str || !*str)
		return (ft_strdup("$"));
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_itoa(shell_errno));
	while (tmp && ft_strncmp(tmp->name, str, ft_strlen(str)))
		tmp = tmp->next;
	if (tmp)
		return (free(str), ft_strdup(tmp->value));
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

char	*ft_expansion(t_env *env, char *str)
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
		expansion = ft_resolve_expansion(env, ft_substr(dollar, 1, i - 1));
		// free(str);
		dollar = ft_strjoin(left, expansion);
		str = ft_strjoin(dollar, right);
		free(left);
		free(right);
		// free(dollar);
		printf("|%s|\n", str);
	}
	return (str);
}

int	main(void)
{
	t_env	env;
	char	*str;

	env.name = 0;
	env.value = 0;
	env.next = 0;
	printf("%s\n", ft_expansion(&env, "$ HOME $USERNAME$HOME"));
}