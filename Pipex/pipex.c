/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:31:08 by mpaterno          #+#    #+#             */
/*   Updated: 2023/03/29 11:49:23 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
int	child_proc(t_pipex *pipex, char **argv, int child_id)
t_pipex	*pipex: t_pipex	*pipex: a pointer to the struct pipex
char **argv:	double pointer that rapresent the preparsed line 
				coming from shell prompt that is already 
				splitted on metacharacter and filtered for '|' or ' '
				
this function do fork for each command setting the pipe array alowing 
the comunication between process.
the stdin and stdout is modyfied as well with dup2 func
*/
int	child_proc(t_shell *shell, char **argv, int child_id)
{
	if (check_built_in(shell, argv[child_id], child_id) == 1)
		return (0);
	sigaction(SIGINT, &shell->a_nothing, 0);
	sigaction(SIGQUIT, &shell->a_nothing, 0);
	shell->pipex.pid[child_id] = fork();
	if (shell->pipex.pid[child_id] < 0)
		return (-1);
	if (shell->pipex.pid[child_id] == 0)
	{
		if (child_id > 0)
			waitpid(shell->pipex.pid[child_id - 1], 0, 0);
		if (child_id == 0 && shell->pipex.cmd_count != 1)
			my_dup(&shell->pipex, child_id, 0);
		else if (child_id == shell->pipex.cmd_count - 1)
			my_dup(&shell->pipex, child_id, 1);
		else
			my_dup(&shell->pipex, child_id, 2);
		close_pipes(&shell->pipex);
		execute_cmd(shell, argv, child_id);
	}
	return (1);
}

/*
int	pipex_init(t_pipex *pipex, int argc, char **argv)
t_pipex	*pipex: a pointer to the struct pipex
int		argc: the number of command given in shell
char **argv:	double pointer that rapresent the preparsed line coming from shell
				prompt that is already splitted on metacharacter and filtered for '|' or ' '

init all variables in pipex struct
*/
int	pipex_init(t_pipex *pipex, int argc, char **argv)
{
	pipex->original_stdout = dup(1);
	pipex->cmd_count = (argc);
	pipex->pipe_count = 2 * (pipex->cmd_count - 1);
	pipex->pipe = (int *)malloc(sizeof(int) * (pipex->pipe_count + 2));
	if (!pipex->pipe)
		return (0);
	pipex->pid = (pid_t *) malloc(sizeof(pid_t) * pipex->cmd_count + 2);
	if (!pipex->pid)
		return (0);
	if (create_pipes(pipex) == -1)
		return (-1);
	pipex->infile_fd = dup(0);
	pipex->outfile_fd = dup(1);
	if (pipex->infile_fd < 0)
	{
		printf("%s: %s: file o directory inesistente\n", argv[1], argv[2]);
		close_pipes(pipex);
		child_free(pipex, 0);
		return (-1);
	}
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

	prepare_strs(argv);
	strs = line_filter(argv);
	if (!strs)
		return (1);
	argc = prepare_strs(strs);
	i = -1;
	if (pipex_init(&shell->pipex, argc, strs) == -1)
		return (2);
	while (++i < shell->pipex.cmd_count)
		if (child_proc(shell, strs, i) < 0)
			return (3);
	close_pipes(&shell->pipex);
	waitpid(shell->pipex.pid[shell->pipex.cmd_count - 1], 0, 0);
	sigaction(SIGINT, &shell->a_int, 0);
	sigaction(SIGQUIT, &shell->a_quit, 0);
	child_free(&shell->pipex, 0);
	ft_free_mat((void ***) &strs);
	return (0);
}
