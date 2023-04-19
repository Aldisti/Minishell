/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:27:33 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/19 13:42:38 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

char	**ft_take_paths(t_shell *shell, int id)
{
	t_list	*node;
	t_env	*elem;
	char	**paths;

	node = ft_get_node(shell->list, "PATH=");
	elem = ft_get_env(node, shell->lvls[id]);
	if (!elem || !elem->value || elem->value[0] == 0)
	{
		paths = ft_split("/", ':');
		if (!paths)
			ft_die(shell, 1, 12);
		return (paths);
	}
	paths = ft_split(elem->value, ':');
	if (!paths)
		ft_die(shell, 1, 12);
	return (paths);
}

void	ft_exit_exec(t_shell *shell, char **argv, char **cmd, int type)
{
	int	i;

	ft_free_mat((void ***) &argv);
	if (type == 3)
	{
		i = 0;
		while (cmd[++i])
			ft_free((void **) &cmd[i]);
		ft_free((void **) &cmd);
		child_free(&shell->pipex, 0);
		ft_die(shell, 1, 127);
	}
	ft_free_mat((void ***) &cmd);
	if (type == 0)
		ft_die(shell, 1, 0);
	else if (type == 1)
	{
		child_free(&shell->pipex, 0);
		ft_die(shell, 1, 1);
	}
	else if (type == 2)
		ft_die(shell, 1, 12);
}

void	ambiguous_red(t_shell *shell, int child_id, char **cmd, char **argv)
{
	if (shell->red.infiles[child_id][0] == '$')
		ft_exit_exec(shell, argv, cmd, fd_printf(2, "%s: ambiguous redirect\n",
				shell->red.infiles[child_id]) * 0 + 1);
	else if (ft_in('<', argv[child_id]))
		ft_exit_exec(shell, argv, cmd,
			fd_printf(2, "%s: no such file or direcory\n",
				shell->red.infiles[child_id]) * 0 + 3);
}

int	ambiguous_red_built(t_shell *shell, int child_id, char **argv)
{
	if (shell->red.infiles[child_id][0] == '$')
	{
		fd_printf(2, "%s: ambiguous redirect\n",
			shell->red.infiles[child_id]);
		g_shell_errno = 1;
		return (0);
	}
	else if (ft_in('<', argv[child_id]))
	{
		fd_printf(2, "%s: no such file or direcory\n",
			shell->red.infiles[child_id]);
		g_shell_errno = 1;
		return (0);
	}
	return (1);
}
