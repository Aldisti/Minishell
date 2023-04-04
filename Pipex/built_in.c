/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:38:07 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/04 21:33:34 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
void	execute_command(char **cmd)
char	**cmd: already properly setted variable that contain the complete
				command retrived from the shell formatted as follow
				{"path/command", "other option or flag", ...}
this function compare the path/command string to different command and 
based on the result execute our own command or senti it to exevec
*/

void	execute_built_in(t_shell *shell, char **cmd, int lvl)
{
	if (!ft_strncmp(cmd[0], "pwd", 3) && ft_strlen(cmd[0]) == 3)
		print_pwd();
	// else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
	// 	return (1);
	else if (!ft_strncmp(cmd[0], "cd", 2) && ft_strlen(cmd[0]) == 2)
		cd(shell, cmd, lvl);
	ft_free_mat((void ***) &cmd);
	// else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
	// 	return (1);
	// else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
	// 	return (1);
	// else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
	// 	return (1);
	// else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
	// 	return (1);
	// else
	// {
	// 	trim_strs(cmd);
	// 	execve(cmd[0], cmd, shell->envp);
	// }
}

/*
int	is_built_in(char *cmd)

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
	ret[++i] = 0;
	return (ret);
}

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
		my_dup(&shell->pipex, *id);
		execute_built_in(shell, ft_split(cmd[(*id)], ' '), 0);
		if (*id > 0)
			close(shell->pipex.pipe[2 * (*id) - 2]);
		else
			close(shell->pipex.pipe[0]);
		close(shell->pipex.pipe[2 * (*id) + 1]);
		if (*id == shell->pipex.cmd_count - 1)
			dup2(shell->pipex.original_stdin, 0);
		return (-1);
	}
	return (flag);
}

void	built_in_pipe_handler(t_shell *shell, int *id, char **cmd)
{
	my_dup(&shell->pipex, (*id) - 1);
	execute_built_in(shell, ft_split(cmd[(*id) - 1], ' '), 0);
	close(shell->pipex.pipe[2 * ((*id)) - 2]);
	close(shell->pipex.pipe[2 * ((*id)) + 1]);
	close(shell->pipex.pipe[2 * ((*id) - 1) + 1]);
	dup2(shell->pipex.original_stdout, 1);
	dup2(shell->pipex.original_stdin, 0);
}
