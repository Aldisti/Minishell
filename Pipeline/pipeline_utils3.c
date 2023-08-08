/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:56:19 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/20 16:22:02 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

/*
char	**line_filter(char **strs)
char **strs:	double pointer that rapresent the preparsed line coming from shell
				prompt that is already splitted on metacharacter.

this function return a new allocated null terminated array that is a copy of strs
but without '|' or ' ' as single string
*/
char	**line_filter(char **strs)
{
	char	**ret;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (strs[++i])
		if (ft_strncmp(strs[i], "|", 1) || (ft_strncmp(strs[i], " ", 1)))
			j++;
	ret = (char **)malloc(sizeof(char *) * (j + 1));
	if (!ret)
		return (0);
	i = -1;
	j = -1;
	while (strs[++i])
	{
		if (!ft_strncmp(strs[i], "|", 1) || (!ft_strncmp(strs[i], " ", 1)))
			continue ;
		ret[++j] = ft_strdup(strs[i]);
		if (!ret[j])
			return (0);
	}
	ret[++j] = 0;
	return (ret);
}

/*
	void	red_sub_proc(t_shell *shell, int *id, int *fd)
	
	set the pipes for the command that is not built in
	accordingly to the position of the command so that
	if is the last command it does not dup the stdout
*/
void	red_sub_proc(t_shell *shell, int *id, int *fd)
{
	dup2(shell->pipex.pipe_fd, 0);
	close(shell->pipex.pipe_fd);
	if ((*id) != shell->pipex.cmd_count - 1)
		dup2(fd[1], 1);
	if (shell->red.outfiles[*id][0])
		red_selector(shell, *id, 2);
	if (shell->red.afiles[*id][0])
		red_selector(shell, *id, 0);
	if (shell->red.infiles[*id][0])
		red_selector(shell, *id, 1);
	close(fd[1]);
	close(fd[0]);
}

/*
	void	parent_stuff(t_shell *shell, int *id, int *fd)

	rapresent the parent process in child_proc, it's role
	is to set the pipe for the nect command if needed
	it also set the error code
*/
void	parent_stuff(t_shell *shell, int *id, int *fd)
{
	int	status;

	if ((*id) != shell->pipex.cmd_count - 1)
	{
		close(shell->pipex.pipe_fd);
		close(fd[1]);
		shell->pipex.pipe_fd = fd[0];
	}
	else if ((*id) == shell->pipex.cmd_count - 1)
	{
		close(shell->pipex.pipe_fd);
		while (waitpid(-1, &status, WUNTRACED) != -1)
			;
		if (WIFEXITED(status))
			g_shell_errno = WEXITSTATUS(status);
		shell->pipex.pipe_fd = dup(0);
	}
}

/*
	void	pipe_ending(t_shell *shell, char **strs)

	the ending part of the pipex func just wait for the last valid
	cmd capture signal and delete the heredoc if created
*/
void	pipe_ending(t_shell *shell, char **strs)
{
	int	i;

	i = -1;
	close(shell->pipex.pipe_fd);
	i = shell->pipex.cmd_count - 1;
	while (i > 0 && shell->pipex.pid[i] != -1)
		i--;
	waitpid(shell->pipex.pid[i], 0, WUNTRACED);
	sigaction(SIGINT, &shell->a_int, 0);
	sigaction(SIGQUIT, &shell->a_quit, 0);
	ft_free_mat((void ***) &strs);
	unlink(".here_doc");
	ft_clear_levels(shell, 1);
}
