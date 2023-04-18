/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:31:08 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/18 21:32:05 by marco            ###   ########.fr       */
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
int	child_proc(t_shell *shell, char **cmd, int *id)
{
	int	flag;
	int	val;

	flag = built_in_selector(shell, id, cmd);
	if (flag < 0)
		return (1);
	val = pre_check(shell, cmd, id);
	if (val > 0)
		return (val);
	val = fork();
	if (val < 0)
		return (-1);
	if (val == 0)
	{
		my_dup(shell, *id);
		pipes(&shell->pipex, "close");
		execute_cmd(shell, cmd, id);
	}
	if (flag)
		built_in_pipe_handler(shell, id, cmd);
	my_wait(shell, *id, val);
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
	i = -1;
	if (pipex_init(&shell->pipex, argc) == -1)
		return (2);
	while (++i < shell->pipex.cmd_count)
		if (child_proc(shell, strs, &i) < 0)
			return (3);
	close_everything(shell);
	sigaction(SIGINT, &shell->a_int, 0);
	sigaction(SIGQUIT, &shell->a_quit, 0);
	child_free(&shell->pipex, 0);
	ft_free_mat((void ***) &strs);
	unlink(".here_doc");
	ft_clear_levels(shell, 1);
	return (0);
}
