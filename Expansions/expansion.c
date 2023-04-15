/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/14 14:08:06 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

int	ft_free_a(char **elem, int n)
{
	if (*elem)
		ft_free((void **)elem);
	elem = 0;
	return (n);
}

char	*ft_exp_tilde(t_shell *shell, char *str, int i)
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

void	ft_expand_all(t_shell *shell, char **parsed)
{
	int	i[3];

	i[1] = -1;
	while (parsed[++i[1]])
	{
		i[0] = -1;
		while (parsed[i[1]][++i[0]])
		{
			i[2] = ft_getquotes(parsed[i[1]], i[0]);
			if (parsed[i[1]][i[0]] == '~' && !i[2])
				parsed[i[1]] = ft_exp_tilde(shell, parsed[i[1]], i[0]);
			else if (parsed[i[1]][i[0]] == '$' && i[2] != 1
					&& (ft_in(parsed[i[1]][i[0] + 1], "*@#?-$!0")
					|| !parsed[i[1]][i[0] + 1]))
				parsed[i[1]] = ft_expand_spec(shell, parsed[i[1]], i[0]);
			else if (parsed[i[1]][i[0]] == '$' && i[2] != 1)
				parsed[i[1]] = ft_expand_doll(shell, parsed[i[1]], i[0]);
			else
				continue ;
			if (i[0] >= (int) ft_strlen(parsed[i[1]]))
				break ;
			if (parsed[i[1]][i[0]] == '$' && !parsed[i[1]][i[0] + 1])
				break ;
		}
	}
}
