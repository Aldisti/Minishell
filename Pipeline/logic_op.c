/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:25:48 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/22 15:49:12 by adi-stef         ###   ########.fr       */
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
	if (!new)
		return (0);
	i = -1;
	while (tab[++i] && start < end)
	{
		new[i] = ft_strdup(tab[start]);
		if (!new[i])
		{
			ft_free_mat((void ***)&new);
			return (NULL);
		}
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
	if (!lvls)
		ft_die(shell, 1, 12);
	i = 0;
	while (start + i <= end)
	{
		lvls[i] = tmp_lvls[start + i];
		i++;
	}
	return (lvls);
}

void	ft_execute(t_shell *shell, int i, int *j)
{
	shell->tmp = ft_subtab(shell->parsed, *j, i);
	if (!shell->tmp)
		ft_die(shell, 1, 12);
	shell->lvls = ft_get_lvls(shell, shell->tmp_lvls, *j, i);
	if (!(*j) || (!g_shell_errno && (*j)
			&& !ft_strcmp(shell->parsed[(*j) - 1], "&&")))
		pipex(shell, shell->tmp);
	else if (g_shell_errno && !ft_strcmp(shell->parsed[(*j) - 1], "||"))
		pipex(shell, shell->tmp);
	*j = i + 1;
	ft_free((void **)&shell->lvls);
	ft_free_mat((void ***)&shell->tmp);
	ft_free((void **) &shell->pipex.pid);
}

void	ft_while(t_shell *shell)
{
	int		tmp_n_cmds;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	while (shell->parsed[len])
		len++;
	shell->tmp_lvls = shell->lvls;
	tmp_n_cmds = shell->n_cmds;
	while (i <= len)
	{
		if (!shell->parsed[i] || !ft_strcmp(shell->parsed[i], "&&")
			|| !ft_strcmp(shell->parsed[i], "||"))
			ft_execute(shell, i, &j);
		i++;
	}
	ft_clear_levels(shell, 1);
	shell->lvls = shell->tmp_lvls;
	shell->n_cmds = tmp_n_cmds;
}
