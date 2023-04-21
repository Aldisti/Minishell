/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:25:48 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/21 16:56:32 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

/*
     0       1          2                       3
echo ciao | ls && grep ';' minishell.h || cat Makefile
     0    1  2  3       4               5       6
*/
char	**ft_subtab(char **tab, int start, int end)
{
	char	**new;
	int		i;

	new = (char **)ft_calloc(end - start + 1, sizeof(char **));
	i = -1;
	while (tab[++i] && start < end)
	{
		new[i] = ft_strdup(tab[start]);
		start++;
	}
	return (new);
}

void	ft_while(t_shell *shell)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (shell->parsed[i])
	{
		if (!ft_strcmp(shell->parsed[i], "&&") || !ft_strcmp(shell->parsed[i], "||"))
		{
			tmp = ft_subtab(shell->parsed, j, i);
			if ((!g_shell_errno && j && !ft_strcmp(shell->parsed[j - 1], "&&")) || !j)
				pipex(shell, tmp);
			else if (g_shell_errno && !ft_strcmp(shell->parsed[j - 1], "||"))
				pipex(shell, tmp);
			j = i + 1;
			ft_free_mat((void ***)&tmp);
			ft_free((void **) &shell->pipex.pid);
		}
		i++;
	}
	tmp = ft_subtab(shell->parsed, j, i);
	if ((!g_shell_errno && j && !ft_strcmp(shell->parsed[j - 1], "&&")) || !j)
		pipex(shell, tmp);
	else if (g_shell_errno && !ft_strcmp(shell->parsed[j - 1], "||"))
		pipex(shell, tmp);
	ft_free_mat((void ***)&tmp);
	ft_free((void **) &shell->pipex.pid);
}