/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:41:00 by marco             #+#    #+#             */
/*   Updated: 2023/03/28 15:33:57 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	is_built_in(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
		return (1);
	else if (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
		return (1);
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

/*
char	*path_checker(t_pipex *pipex)
t_pipex	*pipex	: a pointer to the struct pipex
pipex->paths[i]	:all the possible combination of path/command

this function check if pipex->paths[i] is a valid and existing dir if so return
the string otherwise it print error message and exit
*/

char	*path_checker(t_pipex *pipex, char *str)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	while (pipex->paths[++i] != 0)
	{
		if (!access(pipex->paths[i], X_OK))
		{
			flag = 1;
			break ;
		}	
	}
	if (!flag)
	{
		if (!access(str, X_OK))
			return (ft_strdup(str));
		dup2(pipex->original_stdout, 1);
		printf("%s: comando non trovato\n",
			ft_strrchr(pipex->paths[0], '/') + 1);
		ft_free_mat((void ***) &pipex->paths);
		child_free(pipex, 0);
		exit(1);
	}
	return (ft_strdup(pipex->paths[i]));
}

void	get_cmd_loop(t_pipex *pipex, char *temp, char **command)
{
	temp = ft_strdup(pipex->paths[pipex->cmd_i]);
	free(pipex->paths[pipex->cmd_i]);
	pipex->paths[pipex->cmd_i] = ft_strjoin(temp, "/");
	free(temp);
	temp = ft_strdup(pipex->paths[pipex->cmd_i]);
	free(pipex->paths[pipex->cmd_i]);
	pipex->paths[pipex->cmd_i] = ft_strjoin(temp, command[0]);
	free(temp);
}

/*
char	**get_cmd(t_pipex *pipex, char *str)
t_pipex	*pipex: a pointer to the struct pipex
char	*str: string that contain the command to execute

this function get all the value from env var PATH and check if 
the given command belong to one of that if so join the path with
the actual command and try to execute that, otherwise it will
print error message and exit
*/

char	**get_cmd(t_pipex *pipex, char *str)
{
	char	*temp;
	char	**command;

	pipex->cmd_i = -1;
	pipex->paths = ft_split(getenv("PATH"), ':');
	command = line_filter(command_parser(str, " "));
	if (is_built_in(command[0]) == 0)
	{
		while (pipex->paths[++pipex->cmd_i])
			get_cmd_loop(pipex, temp, command);
		temp = path_checker(pipex, command[0]);
		free(command[0]);
		if (!temp)
			command[0] = 0;
		else
		{
			command[0] = ft_strdup(temp);
			free(temp);
		}
		ft_free_mat((void ***) &pipex->paths);
	}
	return (command);
}
