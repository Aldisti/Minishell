/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:37:43 by marco             #+#    #+#             */
/*   Updated: 2023/04/20 16:29:12 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

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
	cmd = 0;
}

/*
	int	pre_check(t_shell *shell, char **cmd, int *id)

	simple function that check if the executable and if 
	you have the permission to execute
*/
int	pre_check(t_shell *shell, char **cmd, int *id)
{
	sigaction(SIGINT, &shell->a_nothing, 0);
	sigaction(SIGQUIT, &shell->a_nothing, 0);
	if (!ft_strncmp(cmd[*id], "./", 2)
		&& access(ft_strchr(cmd[*id], '/') + 1, F_OK))
		return (g_shell_errno = fd_printf(2, "%s: no such file or directory\n",
				cmd[*id]) * 0 + 127);
	if (!ft_strncmp(cmd[*id], "./", 2)
		&& access(ft_strchr(cmd[*id], '/') + 1, X_OK))
		return (g_shell_errno = fd_printf(2, "%s: permission denied\n",
				cmd[*id]) * 0 + 126);
	return (0);
}

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
