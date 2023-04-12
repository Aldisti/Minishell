/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:31:08 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/12 11:34:55 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int g_shell_errno;

// void	kill_zombie(void)
// {
// 	struct sigaction	sa;
// 	sigset_t			set;

// 	ft_memset(&sa, 0, sizeof(sigaction));
// 	sigemptyset(&set);
// 	sa.sa_mask = set;
// 	sa.sa_handler = SIG_DFL;
// 	sa.sa_flags = SA_NOCLDWAIT;
// 	sigaction(SIGCHLD, &sa, 0);
// }

int	wait_last_valid_pid(t_shell *shell)
{
	int	i;
	int	val;
	int	status;

	i = 0;
	val = -1;
	while (i < shell->pipex.cmd_count)
	{
		if (shell->pipex.pid[i] != -1)
			val = shell->pipex.pid[i];
		i++;
	}
	if (val != -1)
	{
		waitpid(val, &status, 0);
		if (WIFEXITED(status))
			g_shell_errno = WEXITSTATUS(status);
	}
	return (val);
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

	flag = built_in_selector(shell, id, cmd);
	if (flag < 0)
		return (1);
	sigaction(SIGINT, &shell->a_nothing, 0);
	sigaction(SIGQUIT, &shell->a_nothing, 0);
	shell->pipex.pid[*id] = fork();
	if (shell->pipex.pid[*id] < 0)
		return (-1);
	if (shell->pipex.pid[*id] == 0)
	{
		my_dup(shell, *id);
		close_pipes(&shell->pipex);
		execute_cmd(shell, cmd, id);
	}
	if (flag)
		built_in_pipe_handler(shell, id, cmd);
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
	if (create_pipes(pipex) == -1)
		return (-1);
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
	if (pipex_init(&shell->pipex, argc) == -1)
		return (2);
	while (++i < shell->pipex.cmd_count)
	{
		// if (i > 0 && shell->lvls[i] < shell->lvls[i - 1])	
		// 	ft_clean_level(shell, shell->lvls[i - 1]);
		if (child_proc(shell, strs, &i) < 0)
			return (3);
	}
	close_pipes(&shell->pipex);
	wait_last_valid_pid(shell);
	sigaction(SIGINT, &shell->a_int, 0);
	sigaction(SIGQUIT, &shell->a_quit, 0);
	child_free(&shell->pipex, 0);
	ft_free_mat((void ***) &strs);
	// ft_clean_from_lvl(shell, 1);
	unlink(".here_doc");
	return (0);
}
