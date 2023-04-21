/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:08:54 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/21 12:44:24 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

int	ft_continue(t_shell *shell, int n)
{
	if (n == 1 && !shell->line[0])
	{
		g_shell_errno = 0;
		return (1);
	}
	else if (n == 2 && !shell->parsed)
	{
		g_shell_errno = 0;
		return (2);
	}
	else if (n == 3 && (!shell->parsed || !shell->parsed[0]
			|| !shell->parsed[0][0]))
	{
		g_shell_errno = 0;
		return (3);
	}
	return (0);
}

void	ft_shell_set(t_shell *shell)
{
	shell->line = 0;
	shell->parsed = 0;
	shell->envp = 0;
	shell->fd_input = 0;
	shell->fd_output = 0;
	shell->lvls = 0;
	shell->n_cmds = 0;
	shell->files = 0;
	shell->pipex.paths = 0;
	shell->red.infiles = 0;
	shell->red.outfiles = 0;
	shell->pipex.pid = 0;
	shell->red.afiles = 0;
	shell->red.fdin = 0;
	shell->red.fdout = 0;
	shell->red.fda = 0;
	shell->exp.pd = 0;
	shell->exp.sp = 0;
	shell->exp.tmp = 0;
	ft_signals_set(shell);
	shell->envp = list_convert(shell->list, 0);
	if (!shell->envp)
		ft_die(shell, 1, 12);
}
