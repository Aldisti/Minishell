/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:37:43 by marco             #+#    #+#             */
/*   Updated: 2023/04/05 17:02:01 by marco            ###   ########.fr       */
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
int	prepare_strs(char **strs)
{
	int		i;
	char	*temp;

	i = -1;
	while (strs[++i])
	{
		temp = ft_strtrim(strs[i], " ");
		if (!temp)
			exit(1);
		ft_free((void **) &strs[i]);
		strs[i] = ft_strdup(temp);
		if (!strs[i])
			exit(1);
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
void	trim_strs(char **strs, const char *set)
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
				exit(7);
			ft_free((void **) &strs[i]);
			strs[i] = ft_strdup(temp);
			if (!strs[i])
				exit(8);
			ft_free((void **) &temp);
		}
	}
}

/*
SELF EXPLANATORY
*/
void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->pipe_count)
		close(pipex->pipe[i]);
}

void	red_output(t_shell *shell, int id)
{
	int	fd;

	fd = open(shell->red.outfiles[id], O_RDWR);
	dup2(fd, 1);
	close(fd);
}
void	red_input(t_shell *shell, int id)
{
	int	fd;

	fd = open(shell->red.infiles[id], O_RDWR);
	dup2(fd, 0);
	close(fd);
}
void	red_append(t_shell *shell, int id)
{
	int	fd;

	fd = open(shell->red.afiles[id], O_WRONLY | O_APPEND | O_CREAT, 0644);
	dup2(fd, 1);
	close(fd);
}

/*
void	my_dup(t_pipex *pipex, int id)

this is a core func and based on the command id
set the pipe accordingly so that each input and
output is read/write either from/to a pipe or on the
stdout/stdin
*/
void	my_dup(t_shell *shell, int id)
{
	if (id == 0 && shell->pipex.cmd_count != 1)
	{
		if (shell->red.infiles[id][0] != 0)
			red_input(shell, id);
		else
			red_input(shell, id);
		if (shell->red.outfiles[id][0] == 0)
			dup2(shell->pipex.pipe[2 * id + 1], 1);
		else
			red_output(shell, id);
		if (shell->red.afiles[id][0] != 0)
			red_append(shell, id);
	}
	else if ((id == shell->pipex.cmd_count - 1) && id > 0)
	{
		if (shell->red.infiles[id][0] == 0)
			dup2(shell->pipex.pipe[2 * id - 2], 0);
		else
			red_input(shell, id);
		if (shell->red.outfiles[id][0] == 0)
			dup2(shell->pipex.original_stdout, 1);
		else if (shell->red.outfiles[id][0] != 0)
			red_output(shell, id);
		else if (shell->red.afiles[id][0] != 0)
			red_append(shell, id);
	}
	else if ((id == shell->pipex.cmd_count - 1) && id == 0)
	{
		if (shell->red.outfiles[id][0] != 0)
			red_input(shell, id);
		if (shell->red.outfiles[id][0] != 0)
			red_output(shell, id);
		else if (shell->red.afiles[id][0] != 0)
			red_append(shell, id);
	}
	else
	{
		if (shell->red.outfiles[id][0] == 0)
			dup2(shell->pipex.pipe[2 * id - 2], 0);
		else
			red_input(shell, id);
		if (shell->red.outfiles[id][0] == 0)
			dup2(shell->pipex.pipe[2 * id + 1], 1);
		else
			red_output(shell, id);
		if (shell->red.afiles[id][0] != 0)
			red_append(shell, id);
	}
}

/*
SELF EXPLANATORY
*/
int	create_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (pipe(pipex->pipe + 2 * i) == -1)
			return (-1);
	}
	return (1);
}
