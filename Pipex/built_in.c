/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:38:07 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/06 15:00:02 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
void	execute_built_in(t_shell *shell, char **cmd, int lvl)
char	**cmd: already properly setted variable that contain the complete
				builtin command retrived from the shell formatted as follow
				{"command", "other option or flag", ...}
this function compare the command[0] string to different command and if match
it execute our own command
*/
void	execute_built_in(t_shell *shell, char **cmd, int lvl)
{
	if (!ft_strncmp(cmd[0], "pwd", 3) && ft_strlen(cmd[0]) == 3)
		print_pwd();
	else if (!ft_strncmp(cmd[0], "echo", 4) && ft_strlen(cmd[0]) == 4)
		echo(cmd);
	else if (!ft_strncmp(cmd[0], "cd", 2) && ft_strlen(cmd[0]) == 2)
		cd(shell, cmd, lvl);
	else if (!ft_strncmp(cmd[0], "export", 6) && ft_strlen(cmd[0]) == 6)
		ft_export(shell, cmd, lvl);
	else if (!ft_strncmp(cmd[0], "unset", 5) && ft_strlen(cmd[0]) == 5)
		return ;
	else if (!ft_strncmp(cmd[0], "env", 3) && ft_strlen(cmd[0]) == 3)
		env(shell, lvl);
	else if (!ft_strncmp(cmd[0], "exit", 4) && ft_strlen(cmd[0]) == 4)
		ft_die(shell, 1, 69);
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
char	*gnp(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i] && str[i] != ' ')
		;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		exit(20);
	i = -1;
	while (str[++i] && str[i] != ' ')
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

/*
int	built_in_selector(t_shell *shell, int *id, char **cmd)

this func check if the current comman is a builtin and if
the next is not, if so the order is switched and the non-builtin
is executed first otherwise the builtin is execute normally not 
in a sub process
*/
int	built_in_selector(t_shell *shell, int *id, char **cmd)
{
	int	flag;

	flag = 0;
	if (is_blt(gnp(cmd[*id])) && cmd[(*id) + 1] && !is_blt(gnp(cmd[(*id) + 1])))
	{
		flag = 1;
		(*id) += 1;
	}
	else if (is_blt(gnp(cmd[*id])))
	{
		my_dup(shell, *id);
		execute_built_in(shell, ft_split(cmd[(*id)], ' '), 0);
		if (*id > 0)
			close(shell->pipex.pipe[2 * (*id) - 2]);
		else
			close(shell->pipex.pipe[0]);
		close(shell->pipex.pipe[2 * (*id) + 1]);
		if (*id == shell->pipex.cmd_count - 1 && (*id) > 0)
			dup2(shell->pipex.original_stdin, 0);
		dup2(shell->pipex.original_stdout, 1);
		return (-1);
	}
	return (flag);
}

/*
void	built_in_pipe_handler(t_shell *shell, int *id, char **cmd)

this func execute the builtin when the order is switched closing and
dupping the fd properly but only the necessary one
*/
void	built_in_pipe_handler(t_shell *shell, int *id, char **cmd)
{
	my_dup(shell, (*id) - 1);
	execute_built_in(shell, ft_split(cmd[(*id) - 1], ' '), 0);
	close(shell->pipex.pipe[2 * ((*id)) - 2]);
	close(shell->pipex.pipe[2 * ((*id)) + 1]);
	close(shell->pipex.pipe[2 * ((*id) - 1) + 1]);
	dup2(shell->pipex.original_stdout, 1);
	dup2(shell->pipex.original_stdin, 0);
}
