/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:16:34 by marco             #+#    #+#             */
/*   Updated: 2023/04/07 07:37:48 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
	void	red_selector(t_shell *shell, int id, int mode)

	this function open the file target of redirection
	e dup the fd accordingly.
	based on the mode parameter the file is opened in RDWR
	or APPEND, and always based on the mode the output or 
	input is dupped
*/
void	red_selector(t_shell *shell, int id, int mode)
{
	int	fd;

	fd = 0;
	if (mode == 0)
	{
		fd = open(shell->red.afiles[id], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (shell->red.fda[id] != 1)
			dup2(fd, shell->red.fda[id]);
		dup2(fd, 1);
	}
	else if (mode == 1)
	{
		fd = open(shell->red.infiles[id], O_RDWR);
		if (shell->red.fdin[id] != 0)
			dup2(fd, shell->red.fdin[id]);
		dup2(fd, 0);
	}
	else if (mode == 2)
	{
		fd = open(shell->red.outfiles[id], O_RDWR);
		if (shell->red.fdout[id] != 1)
			dup2(fd, shell->red.fdout[id]);
		dup2(fd, 1);
	}
	close(fd);
}

/*
	void	last_cmd_dup(t_shell *shell, int id)

	set the pipes for the current command but only if 
	is the last command in line keeping in mind redirections
*/
void	last_cmd_dup(t_shell *shell, int id)
{
	if (shell->red.infiles[id][0] == 0)
		dup2(shell->pipex.pipe[2 * id - 2], 0);
	else
		red_selector(shell, id, 1);
	if (shell->red.outfiles[id][0] == 0)
		dup2(shell->pipex.original_stdout, 1);
	else if (shell->red.outfiles[id][0] != 0)
		red_selector(shell, id, 2);
	if (shell->red.afiles[id][0] != 0)
		red_selector(shell, id, 0);
}

/*
	void	alone_cmd_dup(t_shell *shell, int id)

	set the pipes for the current command but just
	if is the only command given, keeping in mind redirection
*/
void	alone_cmd_dup(t_shell *shell, int id)
{
	if (shell->red.infiles[id][0] != 0)
		red_selector(shell, id, 1);
	if (shell->red.outfiles[id][0] != 0)
		red_selector(shell, id, 2);
	if (shell->red.afiles[id][0] != 0)
		red_selector(shell, id, 0);
}

/*
	void	middle_cmd_dup(t_shell *shell, int id)

	set the pipe for the current command but only if 
	is in the middle, neither the first nor the last
	keeping in mind the redirection	
*/
void	middle_cmd_dup(t_shell *shell, int id)
{
	if (shell->red.outfiles[id][0] == 0)
		dup2(shell->pipex.pipe[2 * id - 2], 0);
	else
		red_selector(shell, id, 1);
	if (shell->red.outfiles[id][0] == 0)
		dup2(shell->pipex.pipe[2 * id + 1], 1);
	else
		red_selector(shell, id, 2);
	if (shell->red.afiles[id][0] != 0)
		red_selector(shell, id, 0);
}

/*
	void	first_child_dup(t_shell *shell, int id)

	set the pipe for the current command if is the first
	of a set of commands keeping in mind the redirection
	if needed
*/
void	first_child_dup(t_shell *shell, int id)
{
	if (shell->red.infiles[id][0] != 0)
		red_selector(shell, id, 1);
	if (shell->red.outfiles[id][0] == 0)
		dup2(shell->pipex.pipe[2 * id + 1], 1);
	else
		red_selector(shell, id, 2);
	if (shell->red.afiles[id][0] != 0)
		red_selector(shell, id, 0);
}
