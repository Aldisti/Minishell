/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:08:54 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/15 19:28:41 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	shell->pipex.pipe = 0;
	shell->pipex.pid = 0;
	shell->pipex.paths = 0;
	shell->red.infiles = 0;
	shell->red.outfiles = 0;
	shell->red.afiles = 0;
	shell->red.fdin = 0;
	shell->red.fdout = 0;
	shell->red.fda = 0;
	ft_signals_set(shell);
	shell->envp = list_convert(shell->list, 0);
	if (!shell->envp)
		ft_die(shell, 1, 12);
}
