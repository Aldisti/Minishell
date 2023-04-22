/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:31:08 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/21 18:37:07 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

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
	shell->pipex.pipe_fd = dup(0);
	i = -1;
	while (++i < shell->pipex.cmd_count)
		if (child_proc(shell, strs, &i) < 0)
			return (3);
	pipe_ending(shell, strs);
	return (0);
}
