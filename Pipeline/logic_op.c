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
     0       1          2                       3           4
echo ciao | ls && grep ';' minishell.h || cat Makefilei | grep gcc
     0    1  2  3       4               5       6       7    8
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

int	*ft_get_lvls(t_shell *shell, int *tmp_lvls, int start, int end)
{
	int	*lvls;
	int	i;

	start = start / 2;
	end = end / 2;
	(void) shell;
	shell->n_cmds = end - start + 1;
	lvls = (int *)malloc(sizeof(int) * (end - start + 1));
	i = 0;
	while (start + i <= end)
	{
		lvls[i] = tmp_lvls[start + i];
		i++;
	}
	return (lvls);
}

void	ft_while(t_shell *shell)
{
	char	**tmp;
	int	*tmp_lvls;
	int	tmp_n_cmds;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp_lvls = shell->lvls;
	tmp_n_cmds = shell->n_cmds;
	while (shell->parsed[i])
	{
		if (!ft_strcmp(shell->parsed[i], "&&") || !ft_strcmp(shell->parsed[i], "||"))
		{
			tmp = ft_subtab(shell->parsed, j, i);
			shell->lvls = ft_get_lvls(shell, tmp_lvls, j, i);
			if ((!g_shell_errno && j && !ft_strcmp(shell->parsed[j - 1], "&&")) || !j)
				pipex(shell, tmp);
			else if (g_shell_errno && !ft_strcmp(shell->parsed[j - 1], "||"))
				pipex(shell, tmp);
			j = i + 1;
			ft_free((void **)&shell->lvls);
			ft_free_mat((void ***)&tmp);
			ft_free((void **) &shell->pipex.pid);
		}
		i++;
	}
	tmp = ft_subtab(shell->parsed, j, i);
	shell->lvls = ft_get_lvls(shell, tmp_lvls, j, i);
	if ((!g_shell_errno && j && !ft_strcmp(shell->parsed[j - 1], "&&")) || !j)
		pipex(shell, tmp);
	else if (g_shell_errno && !ft_strcmp(shell->parsed[j - 1], "||"))
		pipex(shell, tmp);
	ft_free((void **)&shell->lvls);
	ft_free_mat((void ***)&tmp);
	ft_free((void **) &shell->pipex.pid);
	ft_clear_levels(shell, 1);
	shell->lvls = tmp_lvls;
	shell->n_cmds = tmp_n_cmds;
}
