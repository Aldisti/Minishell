/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/15 12:14:24 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

char	*ft_expand_spec(char *str)
{
	char	*value;

	if (str[1] == '$')
		value = ft_strdup("$");
	else if (str[1] == '?')
		value = ft_itoa(g_shell_errno);
	else
		value = ft_strdup("");
	ft_free((void **)&str);
	return (value);
}

char	*ft_expand_doll(t_shell *shell, char *str, int lvl)
{
	char	*name;
	char	*value;
	t_env	*env;

	name = str + 1;
	env = ft_search_in_list(shell->list, name, lvl);
	if (!env)
		value = ft_strdup("");
	else
		value = ft_strdup(env->value);
	if (!value)
		return (0);
	ft_free((void **)&str);
	return (value);
}

char	*ft_exp_tilde(t_shell *shell, char *str, int lvl)
{
	char	*strs[4];
	int		i;

	i = -1;
	strs[3] = 0;
	while (++i < (int)ft_strlen(str))
	{
		if (str[i] != '~' || (i == 0 && str[i + 1] && !ft_in(str[i + 1],
					MC)) || (i > 0 && ((!ft_in(str[i + 1], MC) && str[i + 1])
					|| (!ft_in(str[i - 1], MC) && str[i - 1]))))
			continue ;
		strs[0] = ft_substr(str, 0, i);
		strs[1] = ft_expand_doll(shell, ft_strdup("$HOME"), lvl);
		if (strs[1] && !ft_strncmp(strs[1], "", 1) && i++)
			strs[1] = ft_strdup("~") + ft_free_a(&strs[1], 0);
		strs[2] = ft_substr(str, i + 1, ft_strlen(str));
		if (!strs[0] || !strs[1] || !strs[2])
			return ((char *)ft_free_mat_a((void ***)&strs, 3));
		i += ft_strlen(strs[1]) - 2;
		ft_free((void **)&str);
		str = ft_joiner(strs, 1);
		if (!str)
			return ((char *)ft_free_mat_a((void ***)&strs, 3));
	}
	return (str);
}

char	**ft_split_expansions(t_shell *shell, char *str, int j, int k)
{
	char	**split;
	int		i[2];

	split = (char **)ft_calloc(ft_countn(str, 36, -1) * 2 + 2, sizeof(char *));
	if (!split)
		ft_die(shell, 1, 12);
	i[0] = 0;
	while (++j <= (int)ft_strlen(str))
	{
		i[1] = ft_getquotes(str, j);
		if (i[1] != 1 && str[j] == '$' && j - k > 0)
			split[i[0]++] = ft_substr(str, k, j - k);
		if (i[1] != 1 && str[j] == '$' && ft_in(str[j + 1], "*@#?-$!0"))
			split[i[0]] = ft_substr(str, j, 2);
		else if (i[1] != 1 && str[j] == '$')
			split[i[0]] = ft_getname(str, j);
		else
			continue ;
		if (!split[i[0]] || (i[0] > 0 && !split[i[0] - 1]))
			return (ft_free_mat_a((void ***)&split, -1));
		k = (j++) + ft_strlen(split[i[0]++]);
	}
	split[i[0]] = ft_substr(str, k, ft_strlen(str));
	return (split);
}

void	ft_expand_all(t_shell *shell, char **parsed)
{
	char	**split;
	int		i;
	int		j;

	j = -1;
	while (parsed[++j])
	{
		if (!ft_in('$', parsed[j]) && !ft_in('~', parsed[j]))
			continue ;
		split = ft_split_expansions(shell, parsed[j], -1, 0);
		if (!split)
			ft_die(shell, 1, 12);
		i = -1;
		while (split[++i])
		{
			if (split[i][0] == '$' && ft_in(split[i][1], "*@#?-$!0"))
				split[i] = ft_expand_spec(split[i]);
			else if (split[i][0] == '$')
				split[i] = ft_expand_doll(shell, split[i], shell->lvls[j]);
			if (ft_countn(split[i], '~', -1))
				split[i] = ft_exp_tilde(shell, split[i], shell->lvls[j]);
		}
		parsed[j] = ft_joiner(split, 1) + ft_free_a(&parsed[j], 0);
		ft_free_mat((void ***)&split);
	}
}
