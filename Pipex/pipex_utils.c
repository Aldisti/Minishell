/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:37:43 by marco             #+#    #+#             */
/*   Updated: 2023/04/18 13:20:05 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
int	prepare_strs(char **strs)
char	**strs: already properly setted variable that contain the complete
				command retrived from the shell formatted as follow
				{"path/command", "other option or flag", ...}

this function loop trought all the string contained in strs and trim
the starting and trailing blank space
*/
int	prepare_strs(t_shell *shell, char **strs)
{
	int		i;
	char	*temp;

	i = -1;
	while (strs[++i])
	{
		temp = ft_strtrim(strs[i], " ");
		if (!temp)
			ft_die(shell, 1, 12);
		ft_free((void **) &strs[i]);
		strs[i] = ft_strdup(temp);
		if (!strs[i])
			ft_die(shell, 1, 12);
		ft_free((void **) &temp);
	}
	return (i);
}

/*
int	prepare_strs(char **strs)
char	**strs: already properly setted variable that contain the complete
				command retrived from the shell formatted as follow
				{"path/command", "other option or flag", ...}

this function loop trought all the string contained in strs and trim
the starting and trailing ["] or [']
*/
void	trim_strs(t_shell *shell, char **strs, const char *set)
{
	char	*temp;
	int		i;

	i = -1;
	while (strs[++i])
	{
		if (!ft_strncmp(strs[i], set, 1))
		{
			temp = ft_strtrim(strs[i], set);
			if (!temp)
				ft_die(shell, 1, 12);
			ft_free((void **) &strs[i]);
			strs[i] = ft_strdup(temp);
			if (!strs[i])
				ft_die(shell, 1, 12);
			ft_free((void **) &temp);
		}
	}
}

/*
void	child_free(t_pipex *pipex, char **cmd)
t_pipex	*pipex: a pointer to pipex struct
char	**cmd: the allocated command to free

this function free and sett all the allocated variablesto 0
and close all the fd including the original stdout
*/
void	child_free(t_pipex *pipex, char **cmd)
{
	int	i;

	i = -1;
	close(pipex->original_stdin);
	close(pipex->original_stdout);
	while (cmd && cmd[++i])
		ft_free((void **) &cmd[i]);
	if (cmd)
		ft_free((void **) &cmd);
	ft_free((void **) &pipex->pipe);
	pipex->pipe = 0;
	cmd = 0;
}

/*
	int	pipes(t_pipex *pipex, const char *mode)

	func that create or close pipes based on
	the mode argument and return 1 if all is 
	good
*/
int	pipes(t_pipex *pipex, const char *mode)
{
	int	i;

	i = -1;
	if (!ft_strncmp(mode, "open", 4))
	{
		while (++i < pipex->cmd_count)
		{
			if (pipe(pipex->pipe + 2 * i) == -1)
				return (-1);
		}
	}
	else
	{
		while (++i < pipex->pipe_count)
			close(pipex->pipe[i]);
	}
	return (1);
}

/*
void	my_dup(t_pipex *pipex, int id)

this is a core func and based on the command id
set the pipe accordingly so that each input and
output is read/write either from/to a pipe or on the
stdout/stdin it also set redirection based on the specific
cases
*/
void	my_dup(t_shell *shell, int id)
{
	if (id == 0 && shell->pipex.cmd_count != 1)
		first_child_dup(shell, id);
	else if ((id == shell->pipex.cmd_count - 1) && id > 0)
		last_cmd_dup(shell, id);
	else if ((id == shell->pipex.cmd_count - 1) && id == 0)
		alone_cmd_dup(shell, id);
	else
		middle_cmd_dup(shell, id);
}
