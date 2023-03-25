/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:35:10 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/24 15:28:55 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_shell_errno;

char	*ft_resolve_expansion(t_list *list, char *str, int lvl)
{
	t_env	*tmp;

	if (!str || !*str || !ft_strncmp(str, "$", ft_strlen(str)))
		return (ft_strdup(""));
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_itoa(g_shell_errno));
	tmp = ft_search_in_list(list, str, lvl);
	if (!tmp)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

char	*ft_check_quote(t_list *list, char *str, int *i)
{
	static int	quotes;
	char		*strs[4];

	strs[3] = 0;
	if (str[*i] == '~' && !quotes)
	{
		strs[0] = ft_substr(str, 0, *i);
		strs[1] = ft_resolve_expansion(list, "HOME",
				(ft_countn(str, '(', *i) - ft_countn(str, ')', *i)));
		strs[2] = ft_substr(str, *i + 1, ft_strlen(str) - *i - 1);
		free(str);
		str = ft_joiner(strs, 1);
	}
	if (str[*i] == '\"' && !quotes)
		quotes = 1;
	else if (str[*i] == '\"' && quotes)
		quotes = 0;
	if (str[*i] == '\'' && !quotes)
		while (str[++(*i)] != '\'')
			;
	return (str);
}

char	*ft_expansion(t_shell *shell, char *str)
{
	int		index[2];
	char	*strs[5];

	index[0] = -1;
	strs[4] = 0;
	while (str[++index[0]])
	{
		str = ft_check_quote(shell->list, str, &index[0]);
		if (str[index[0]] != '$')
			continue ;
		strs[0] = ft_substr(str, 0, index[0]);
		index[1] = index[0] + 1;
		while (str[index[1]] && !ft_in(str[index[1]], "$ ()\'\""))
			index[1]++;
		strs[2] = ft_substr(str, index[1], ft_strlen(str) - index[1]);
		strs[3] = ft_substr(str, index[0] + 1, index[1] - index[0] - 1);
		strs[1] = ft_resolve_expansion(shell->list, strs[3],
				(ft_countn(str, '(', index[0]) - ft_countn(str, ')', index[0])));
		free(strs[3]);
		strs[3] = 0;
		free(str);
		str = ft_joiner(strs, 1);
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

// int	main(void)
// {
// 	t_shell	shell;
// 	t_env	env;
// 	t_env	env2;
// 	t_env	env3;
// 	t_list	list;
// 	t_list	list2;
// 	char	*str;

// 	env.name = "HOME";
// 	env.value = "/home/adi-stef";
// 	env.level = 0;
// 	env.next = &env2;
// 	env2.name = "HOME";
// 	env2.value = "1";
// 	env2.level = 1;
// 	env2.next = &env3;
// 	env3.name = "HOME";
// 	env3.value = "ciccia";
// 	env3.level = 2;
// 	env3.next = 0;
// 	shell.list = &list;
// 	list.content = &env;
// 	shell.list->next = 0;
// 	// list2.content = &env2;
// 	// list2.next = 0;
// 	str = ft_expansion(&shell, ft_strdup("$HOME((''$HOME'')\"$HOME\")~"));
// 	printf("\n<%s>\n", str);
// 	free(str);
// 	return (0);
// }