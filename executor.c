/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:35:10 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/23 16:23:00 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_errno = 169;

char	*ft_resolve_expansion(t_list *list, char *str, int lvl)
{
	t_env	tmp;

	if (!str || !*str)
		return (ft_strdup(""));
	if (!ft_strncmp(str, "$", ft_strlen(str)))
		return (ft_strdup(""));
	if (!ft_strncmp(str, "?", ft_strlen(str)))
		return (ft_itoa(shell_errno));
	while (list && ft_strncmp(list->content->name, str, ft_strlen(str)))
		list = list->next;
	if (!list)
		return (ft_strdup(""));
	tmp = *(list->content);
	while (tmp.next && tmp.level != lvl)
		tmp = *(tmp.next);
	if (!ft_strncmp(tmp.name, str, ft_strlen(str)) && tmp.level == lvl)
		return (ft_strdup(tmp.value));
	else
		ft_strdup("");
}

int	ft_ifin(char c, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

int	ft_check_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i + 1] && str[i] == '$' && !ft_ifin(str[i + 1], "$ ()'\""))
			return (i);
	return (-1);
}

// char	*ft_expand_tilde(t_list *list, char *str)
// {
// 	int		i;
// 	t_env	*env;
// 	char	*left;
// 	char	*right;
// 	char	*tmp;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '~'
// 				&& !(ft_countn(str, 34, i) - ft_countn(str, 34, i) % 2)
// 				&& !(ft_countn(str, 39, i) - ft_countn(str, 39, i) % 2))
// 		{
// 			left = ft_substr(str, 0, i);
// 			right = ft_substr(str, i + 1, ft_strlen(str) - i);
// 			while (ft_strncmp(list->content->name, "HOME", 4))
// 				list = list->next;
// 			env = list->content;
// 			while ()
// 		}
// 	}
// }

char	*ft_expansion(t_shell *shell, char *str)
{
	int		i;
	int		brackets;
	char	*strs[4];
	char	*dollar;

	brackets = 0;
	strs[3] = 0;
	// str = ft_expand_tilde(shell->list, str);
	while (ft_check_dollar(str) != -1)
	{
		dollar = str + ft_check_dollar(str);
		i = 1;
		while (dollar[i] && !ft_ifin(dollar[i], "$ ()'\""))
			i++;
		str = 
		strs[0] = ft_substr(str, 0, dollar - str);
		strs[2] = ft_substr(dollar, i, ft_strlen(dollar) - i + 1);
		brackets = ft_countn(str, '(', ft_check_dollar(str)) - ft_countn(str, ')', ft_check_dollar(str));
		// printf("brackets in |%s| at %d i are %d\n", str, ft_check_dollar(str), brackets);
		strs[1] = ft_resolve_expansion(shell->list, ft_substr(dollar, 1, i - 1), brackets);
		// free(str);
		str = ft_joiner(strs, 1);
	}
	return (str);
}

int	main(void)
{
	t_shell	shell;
	t_env	env;
	t_env	env2;
	t_env	env3;
	t_list	list;
	t_list	list2;
	char	*str;

	env.name = "HOME";
	env.value = "casa";
	env.level = 0;
	env.next = &env2;
	env2.name = "HOME";
	env2.value = "1";
	env2.level = 1;
	env2.next = &env3;
	env3.name = "HOME";
	env3.value = "ciccia";
	env3.level = 2;
	env3.next = 0;
	shell.list = &list;
	list.content = &env;
	shell.list->next = 0;
	// list2.content = &env2;
	// list2.next = 0;
	printf("\n<%s>\n", ft_expansion(&shell, "$HOME(('$HOME')$HOME)"));
}