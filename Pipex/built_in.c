/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:38:07 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/03 21:35:45 by marco            ###   ########.fr       */
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

int	is_built_in(char *cmd)
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

char	*get_cmd_no_path(char *str)
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

/*
int	check_built_in(t_shell *shell, char *str)
char	*str: string that contain the command to execute

this func controll the passed string and check if the
command is a built in, if so it execute before the creation
of the forked porcess
*/

// int	check_built_in(t_shell *shell, char *str, int child_id)
// {
// 	char	**temp;

// 	shell->pipex.pid[child_id] = -1;
// 	temp = ft_split(str, ' ');
// 	if (!temp)
// 		exit(6);//ft_die
// 	if (is_built_in(temp[0]))
// 		execute_built_in(shell, temp, 0);
// 	else
// 	{
// 		ft_free_mat((void ***)&temp);
// 		return (0);
// 	}
// 	ft_free_mat((void ***)&temp);
// 	return (1);
// }
