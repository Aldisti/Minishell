/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:38:07 by mpaterno          #+#    #+#             */
/*   Updated: 2023/03/28 20:54:11 by marco            ###   ########.fr       */
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

int	is_built_in(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (0);
	else if (!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
		return (1);
	else if (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
		return (1);
	else if (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4)
		return (1);
	return (0);
}
