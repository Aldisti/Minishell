/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:52:04 by marco             #+#    #+#             */
/*   Updated: 2023/04/18 15:54:25 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

int	pre_check(t_shell *shell, char **cmd, int *id)
{
	sigaction(SIGINT, &shell->a_nothing, 0);
	sigaction(SIGQUIT, &shell->a_nothing, 0);
	if (!ft_strncmp(cmd[*id], "./", 2)
		&& access(ft_strchr(cmd[*id], '/') + 1, W_OK))
		return (g_shell_errno = fd_printf(2, "%s: no such file or directory\n",
				cmd[*id]) * 0 + 127);
	while (special_cat(shell, cmd, *id)
		&& (shell->pipex.is_first || (*id) == 0))
	{
		shell->pipex.flag++;
		(*id)++;
	}
	return (0);
}
