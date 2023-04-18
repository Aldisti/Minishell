/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:29:02 by marco             #+#    #+#             */
/*   Updated: 2023/04/18 12:29:55 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
int	pipex_init(t_pipex *pipex, int argc, char **argv)
t_pipex	*pipex: a pointer to the struct pipex
int		argc: the number of command given in shell
char **argv:	double pointer that rapresent the preparsed line coming from shell
				prompt that is already splitted on metacharacter and filtered for '|' or ' '

init all variables in pipex struct
*/
int	pipex_init(t_pipex *pipex, int argc)
{
	int	i;

	i = -1;
	pipex->original_stdout = dup(1);
	pipex->original_stdin = dup(0);
	pipex->cmd_count = (argc);
	pipex->pipe_count = 2 * (pipex->cmd_count - 1);
	pipex->pipe = (int *)malloc(sizeof(int) * (pipex->pipe_count + 2));
	if (!pipex->pipe)
		return (0);
	pipex->pid = (pid_t *) malloc(sizeof(pid_t) * pipex->cmd_count + 2);
	if (!pipex->pid)
		return (0);
	while (++i < pipex->cmd_count)
		pipex->pid[i] = -1;
	if (pipes(pipex, "open") == -1)
		return (-1);
	return (1);
}