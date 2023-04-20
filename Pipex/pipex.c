/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:31:08 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/20 15:10:10 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

void	my_wait(t_shell *shell, int id, int process_id)
{
	int		status;

	waitpid(process_id, &status, 0);
	if ((id) > 0)
		close(shell->pipex.pipe[2 * (id) - 2]);
	close(shell->pipex.pipe[2 * (id) + 1]);
	if (WIFEXITED(status))
		g_shell_errno = WEXITSTATUS(status);
}

/*
int	child_proc(t_pipex *pipex, char **argv, int child_id)
t_pipex	*pipex: t_pipex	*pipex: a pointer to the struct pipex
char **argv:	double pointer that rapresent the preparsed line 
				coming from shell prompt that is already 
				splitted on metacharacter and filtered for '|' or '
				
this function do fork for each command setting the pipe array alowing 
the comunication between process.
the stdin and stdout is modyfied as well with dup2 func
*/
// int	child_proc(t_shell *shell, char **cmd, int *id)
// {
// 	int	flag;
// 	int	val;

// 	flag = built_in_selector(shell, id, cmd);
// 	if (flag < 0)
// 		return (1);
// 	val = pre_check(shell, cmd, id);
// 	if (val > 0)
// 		return (val);
// 	val = fork();
// 	if (val < 0)
// 		return (-1);
// 	if (val == 0)
// 	{
// 		my_dup(shell, *id);
// 		pipes(&shell->pipex, "close");
// 		execute_cmd(shell, cmd, id);
// 	}
// 	my_wait(shell, *id, val);
// 	return (1);
// }

void	red_sub_proc(t_shell *shell, int *id, int *fd)
{
	dup2(shell->pipex.temp_flag, 0);
	close(shell->pipex.temp_flag);
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

void	parent_stuff(t_shell *shell, int *id, int *fd)
{
	int	status;

	if ((*id) != shell->pipex.cmd_count - 1)
	{
		close(shell->pipex.temp_flag);
		close(fd[1]);
		shell->pipex.temp_flag = fd[0];
	}
	else if ((*id) == shell->pipex.cmd_count - 1)
	{
		close(shell->pipex.temp_flag);
		while (waitpid(-1, &status, WUNTRACED) != -1)
			;
		if (WIFEXITED(status))
			g_shell_errno = WEXITSTATUS(status);
		shell->pipex.temp_flag = dup(0);
	}
}

int	child_proc(t_shell *shell, char **cmd, int *id)
{
	int	fd[2];
	int	temp;

	if (pipe(fd) == -1)
		return (-1);
	temp = pre_check(shell, cmd, id);
	if (temp > 0)
		return (temp);
	if (built_in_selector(shell, id, cmd, fd) == -1)
		return (1);
	shell->pipex.pid[*id] = fork();
	if (shell->pipex.pid[*id] == 0)
	{
		red_sub_proc(shell, id, fd);
		execute_cmd(shell, cmd, id);
	}
	else
		parent_stuff(shell, id, fd);
	return (1);
}

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
int	pipex(t_shell *shell, char **argv)
t_pipex	*pipex: a pointer to the struct pipex
char **argv:	double pointer that rapresent the preparsed line
				coming from shell prompt that is already splitted
				on metacharacter and filtered for '|' or ' '

the function basically first prepare the input then set the pipex
struct and call as many child process as commands given by the shell
linking them with pipe then wait all the created process e finish execution
*/
int	pipex(t_shell *shell, char **argv)
{
	char	**strs;
	int		argc;
	int		i;

	prepare_strs(shell, argv);
	strs = line_filter(argv);
	if (!strs)
		return (1);
	argc = prepare_strs(shell, strs);
	if (pipex_init(&shell->pipex, argc) == -1)
		return (2);
	shell->pipex.temp_flag = dup(0);
	i = -1;
	while (++i < shell->pipex.cmd_count)
		if (child_proc(shell, strs, &i) < 0)
			return (3);
	close(shell->pipex.temp_flag);
	i = shell->pipex.cmd_count - 1;
	while (i > 0 && shell->pipex.pid[i] != -1)
		i--;
	waitpid(shell->pipex.pid[i], 0, WUNTRACED);
	sigaction(SIGINT, &shell->a_int, 0);
	sigaction(SIGQUIT, &shell->a_quit, 0);
	child_free(&shell->pipex, 0);
	ft_free_mat((void ***) &strs);
	unlink(".here_doc");
	ft_clear_levels(shell, 1);
	return (0);
}
