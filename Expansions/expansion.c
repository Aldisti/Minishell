/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/25 18:05:37 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

//	echo (~) da discutere
char	*ft_expand_tilde(t_shell *shell, char *str, int i)
{
	char	*strs[4];
	char	*tmp;
	t_env	*env;

	if ((str[i + 1] && !ft_in(str[i + 1], METACHARS) && str[i + 1] != '/')
			|| (i > 0 && !ft_in(str[i - 1], METACHARS) && str[i - 1] != '/'))
		return (str);
	strs[3] = 0;
	env = ft_search_in_list(shell->list, "HOME", ft_getlvl(str, i));
	if (!env)
		return (str);
	strs[0] = ft_substr(str, 0, i);
	if (!strs[0] && i > 0)
		exit(1); // ft_die(shell)
	strs[2] = ft_substr(str, i + 1, ft_strlen(str));
	if (!strs[2] && (ft_strlen(str) - i - 1))
		exit(1); // ft_die(shell)
	strs[1] = ft_strdup(env->value);
	if (!strs[1] && ft_strlen(env->value))
		exit(1); // ft_die(shell)
	tmp = ft_joiner(strs, 1);
	if (!tmp)
		exit(1); // ft_die(shell)
	free(str);
	return (tmp);
}

char	*ft_expand_dollar(t_shell *shell, char *str, int i)
{
	char	*strs[4];
	char	*tmp;
	t_env	*env;

	if (ft_getquotes(str, i) == 1)
		return (str);
	// if (str[i + 1] && (str[i + 1] == '?' || str[i + 1] == '$'))
	// 	return (ft_expand_special(shell, str, i));
	strs[3] = 0;
	tmp = ft_getname(str, i);
	// printf("|%s|\n", tmp);
	if (!tmp)
		exit(1); // ft_die(shell)
	env = ft_search_in_list(shell->list, tmp, ft_getlvl(str, i));
	if (!env)
		return (str);
	strs[0] = ft_substr(str, 0, i);
	if (!strs[0] && i > 0)
		exit(1); // ft_die(shell)
	strs[2] = ft_substr(str, i + ft_strlen(tmp) + 1, ft_strlen(str));
	// printf("right: |%s|\n", &str[ft_strlen(tmp) + i - 1]);
	if (!strs[1] && ft_strlen(env->value))
		exit(1); // ft_die(shell)
	strs[1] = ft_strdup(env->value);
	if (!strs[1] && ft_strlen(env->value))
		exit(1); // ft_die(shell)
	// printf("ciao\n");
	free(tmp);
	tmp = ft_joiner(strs, 1);
	free(str);
	// printf("|%s|\n", tmp);
	// exit(1);
	return (tmp);
}

char	*ft_expansion(t_shell *shell, char *str)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (str[++i])
	{
		if (str[i] == '~' && !ft_getquotes(str, i))
			str = ft_expand_tilde(shell, str, i);
		else if (str[i] == '$' && ft_getquotes(str, i) != 1)
			str = ft_expand_dollar(shell, str, i);
	}
	return (str);
}

char	**ft_expand_all(t_shell *shell)
{
	int		i;
	char	*tmp;

	i = -1;
	while (shell->parsed[++i])
	{
		tmp = ft_expansion(shell, shell->parsed[i]);
		shell->parsed[i] = tmp;
	}
	return (shell->parsed);
}