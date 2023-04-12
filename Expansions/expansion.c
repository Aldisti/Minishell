/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/12 08:42:15 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

int	ft_free_a(char **elem, int n)
{
	if (elem)
		free(elem);
	elem = 0;
	return (n);
}

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
		ft_die(shell, 1, 12);
	strs[2] = ft_substr(str, i + 1, ft_strlen(str));
	if (!strs[2] && (ft_strlen(str) - i - 1))
		ft_die(shell, ft_free_a(&strs[0], 1), 12);
	strs[1] = ft_strdup(env->value);
	if (!strs[1] && ft_strlen(env->value))
		ft_die(shell, ft_free_a(&strs[2], 1), ft_free_a(&strs[0], 12));
	tmp = ft_joiner(strs, 1);
	if (!tmp)
		ft_die(shell, 1, 12);
	ft_free((void **)&str);
	return (tmp);
}

char	*ft_expand_spec(t_shell *shell, char *str, int i)
{
	char	*strs[4];

	if (!str[i + 1])
		return (str);
	strs[3] = 0;
	strs[0] = ft_substr(str, 0, i);
	strs[2] = ft_substr(str, i + 2, ft_strlen(str));
	if (!strs[0] || !strs[2])
		ft_die(shell, ft_free_a(&strs[0], 1), ft_free_a(&strs[2], 12));
	if (str[i + 1] == '?')
		strs[1] = ft_itoa(g_shell_errno);
	else if (str[i + 1] == '$')
		strs[1] = ft_strdup("$");
	else
		strs[1] = ft_strdup("");
	if (!strs[1])
		ft_die(shell, ft_free_a(&strs[1], 1), 12);
	strs[3] = ft_joiner(strs, 1);
	if (!strs[3])
		ft_die(shell, 1, 12);
	ft_free((void **)&str);
	return (strs[3]);
}

char	*ft_expand_doll(t_shell *shell, char *str, int i)
{
	char	*strs[4];
	t_env	*env;

	strs[3] = ft_getname(str, i);
	if (!strs[3])
		ft_die(shell, 1, 12);
	env = ft_search_in_list(shell->list, strs[3], ft_getlvl(str, i));
	if (!env)
		strs[1] = ft_strdup("");
	else
		strs[1] = ft_strdup(env->value);
	strs[0] = ft_substr(str, 0, i);
	strs[2] = ft_substr(str, i + ft_strlen(strs[3]) + 1, ft_strlen(str));
	if (!strs[0] || !strs[1] || !strs[2])
		ft_die(shell, ft_free_a(&strs[0], ft_free_a(&strs[1], 1)),
			ft_free_a(&strs[2], 12));
	ft_free((void **)&strs[3]);
	strs[3] = ft_joiner(strs, 1);
	ft_free((void **)&str);
	return (strs[3]);
}

void	ft_expand_all(t_shell *shell)
{
	int	i;
	int	j;
	int	quotes;

	j = -1;
	while (shell->parsed[++j])
	{
		i = -1;
		while (shell->parsed[j][++i])
		{
			quotes = ft_getquotes(shell->parsed[j], i);
			if (shell->parsed[j][i] == '~' && !quotes)
				shell->parsed[j] = ft_expand_tilde(shell, shell->parsed[j], i);
			else if (shell->parsed[j][i] == '$' && quotes != 1
					&& (ft_in(shell->parsed[j][i + 1], "*@#?-$!0")
					|| !shell->parsed[j][i + 1]))
				shell->parsed[j] = ft_expand_spec(shell, shell->parsed[j], i);
			else if (shell->parsed[j][i] == '$' && quotes != 1)
				shell->parsed[j] = ft_expand_doll(shell, shell->parsed[j], i);
			else
				continue ;
			if (i >= (int) ft_strlen(shell->parsed[j]))
				i = ft_strlen(shell->parsed[j]) - 1;
			if (!(shell->parsed[j][i] == '$' && !shell->parsed[j][i + 1]))
				i--;
		}
	}
}
