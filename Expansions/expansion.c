/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/17 13:47:24 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

typedef struct s_exp
{
	char	**split;
	char	**parsed;
	char	*strs[4];
}	t_exp;

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

char	*ft_exp_dol(t_shell *shell, char *str, int lvl)
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
	if (ft_check_for_space(value) && ft_check_for_op(&shell->exp, str))
		return (str + ft_free_a(&value, 0));
	if (!value)
		return (0);
	ft_free((void **)&str);
	if (ft_in('>', value) || ft_in('|', value) || ft_in('<', value))
		value = ft_put_quotes(shell, value);
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
		strs[1] = ft_exp_dol(shell, ft_strdup("$HOME"), lvl);
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

void	ft_split_expansions(t_shell *sh, char *str, int j, int k)
{
	int		i[2];

	sh->exp.sp = (char **)ft_calloc(ft_countn(str, 36, -1) * 2 + 2,
			sizeof(char *));
	if (!sh->exp.sp)
		ft_die(sh, 1, 12);
	i[0] = 0;
	while (++j <= (int)ft_strlen(str))
	{
		i[1] = ft_getquotes(str, j);
		if (i[1] != 1 && str[j] == '$' && j - k > 0)
			sh->exp.sp[i[0]++] = ft_substr(str, k, j - k);
		if (i[1] != 1 && str[j] == '$' && ft_in(str[j + 1], "*@#?-$!0"))
			sh->exp.sp[i[0]] = ft_substr(str, j, 2);
		else if (i[1] != 1 && str[j] == '$')
			sh->exp.sp[i[0]] = ft_getname(str, j);
		else
			continue ;
		if (!sh->exp.sp[i[0]] || (i[0] > 0 && !sh->exp.sp[i[0] - 1]))
			ft_die(sh, 1, 12);
		k = (j++) + ft_strlen(sh->exp.sp[i[0]++]);
	}
	sh->exp.sp[i[0]] = ft_substr(str, k, ft_strlen(str));
	if (!sh->exp.sp[i[0]])
		ft_die(sh, 1, 12);
}

void	ft_expand_all(t_shell *sh, char **parsed)
{
	int		i;
	int		j;

	j = -1;
	while (parsed[++j])
	{
		if (!ft_in('$', parsed[j]) && !ft_in('~', parsed[j]))
			continue ;
		ft_split_expansions(sh, parsed[j], -1, 0);
		if (!sh->exp.sp)
			ft_die(sh, 1, 12);
		i = -1;
		while (sh->exp.sp[++i])
		{
			if (sh->exp.sp[i][0] == '$' && ft_in(sh->exp.sp[i][1], "*@#?-$!0"))
				sh->exp.sp[i] = ft_expand_spec(sh->exp.sp[i]);
			else if (sh->exp.sp[i][0] == '$')
				sh->exp.sp[i] = ft_exp_dol(sh, sh->exp.sp[i], sh->lvls[j]);
			if (ft_countn(sh->exp.sp[i], '~', -1))
				sh->exp.sp[i] = ft_exp_tilde(sh, sh->exp.sp[i], sh->lvls[j]);
		}
		parsed[j] = ft_joiner(sh->exp.sp, 1) + ft_free_a(&parsed[j], 0);
		ft_free_exp(&sh->exp);
	}
}
