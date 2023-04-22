/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:38:07 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/21 20:51:07 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

/*
void	execute_built_in(t_shell *shell, char **cmd, int lvl)
char	**cmd: already properly setted variable that contain the complete
				builtin command retrived from the shell formatted as follow
				{"command", "other option or flag", ...}
this function compare the command[0] string to different command and if match
it execute our own command
*/
void	execute_built_in(t_shell *shell, char **strs, int lvl, int id)
{
	char	**temp;
	char	**cmd;

	temp = ft_parser(shell, strs[id], " ");
	cmd = line_filter(temp);
	ft_free_mat((void ***) &temp);
	if (!ft_strncmp(cmd[0], "pwd", 3) && ft_strlen(cmd[0]) == 3)
		g_shell_errno = print_pwd(shell);
	else if (!ft_strncmp(cmd[0], "echo", 4) && ft_strlen(cmd[0]) == 4)
		g_shell_errno = echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 2) && ft_strlen(cmd[0]) == 2)
		g_shell_errno = cd(shell, cmd, lvl);
	else if (!ft_strncmp(cmd[0], "export", 6) && ft_strlen(cmd[0]) == 6)
		g_shell_errno = ft_export(shell, cmd, lvl);
	else if (!ft_strncmp(cmd[0], "unset", 5) && ft_strlen(cmd[0]) == 5)
		g_shell_errno = ft_unset(shell, cmd, lvl);
	else if (!ft_strncmp(cmd[0], "env", 3) && ft_strlen(cmd[0]) == 3)
		g_shell_errno = env(shell, cmd, lvl);
	else if (!ft_strncmp(cmd[0], "exit", 4) && ft_strlen(cmd[0]) == 4)
		g_shell_errno = ft_exit(shell, strs, cmd);
	ft_free_mat((void ***) &cmd);
}

/*
int	is_blt(char *cmd)

this func just compare the string and check if the command is a builtin
command if so 1 is returned
*/
int	is_blt(char *cmd)
{
	int	flag;

	flag = 0;
	if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		flag = 1;
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		flag = 1;
	else if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		flag = 1;
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		flag = 1;
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		flag = 1;
	else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		flag = 1;
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		flag = 1;
	ft_free((void **) &cmd);
	if (!flag)
		return (0);
	return (1);
}

/*
char	*gnp(char *str)

this func return an allocate char *
that is just the str passed as argument
trimmed at the first blank space found so that 
can be used to check if the command is a builtin
*/
char	*gnp(t_shell *shell, char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i] && str[i] != ' ')
		;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		ft_die(shell, 1, 12);
	i = -1;
	while (str[++i] && str[i] != ' ')
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

void	built_in_check(t_shell *shell, int *id, char **cmd, int *fd)
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
	ft_replace(cmd[*id], "\37", ' ');
	if (ft_in('>', cmd[*id]) && shell->red.outfiles[*id][0])
	{
		fd_printf(2, "%s: no such file or directory\n",
			ft_strchr(cmd[*id], '>') + 1);
		g_shell_errno = 1;
		return ;
	}
	execute_built_in(shell, cmd, shell->lvls[*id], *id);
	shell->pipex.pipe_fd = fd[0];
	dup2(shell->pipex.original_stdout, 1);
	dup2(shell->pipex.original_stdin, 0);
}

/*
int	built_in_selector(t_shell *shell, int *id, char **cmd)

this func check if the current comman is a builtin and if
the next is not, if so the order is switched and the non-builtin
is executed first otherwise the builtin is execute normally not 
in a sub process
*/
int	built_in_selector(t_shell *shell, int *id, char **cmd, int *fd)
{
	int		flag;

	flag = 0;
	if (!ambiguous_red_built(shell, *id, cmd))
		return (-1);
	if (is_blt(gnp(shell, cmd[*id])))
	{
		if ((!ft_in2('<', cmd[*id]) && shell->red.infiles[*id][0]))
			return (0);
		built_in_check(shell, id, cmd, fd);
		return (-1);
	}
	return (flag);
}
