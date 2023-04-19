/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:41:00 by marco             #+#    #+#             */
/*   Updated: 2023/04/19 18:59:06 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
char	*path_checker(t_pipex *pipex)
t_pipex	*pipex	: a pointer to the struct pipex
pipex->paths[i]	:all the possible combination of path/command

this function check if pipex->paths[i] is a valid and existing dir if so return
the string otherwise it print error message and exit
*/
char	*path_checker(t_shell *shell, t_pipex *pipex, char **str, int i)
{
	int	flag;

	flag = 0;
	while (pipex->paths[++i] != 0)
	{
		if (!access(pipex->paths[i], X_OK))
		{
			flag = 1;
			break ;
		}	
	}
	if (flag)
		return (ft_strdup(pipex->paths[i]));
	if (!access(str[0], X_OK) && ft_get_node(shell->list, "PATH")
		&& ft_find_in_array(shell->files, str[0]) == -1)
		return (ft_strdup(str[0]));
	if (!access(str[0], X_OK) && !ft_get_node(shell->list, "PATH")
		&& ft_find_in_array(shell->files, str[0]) != -1)
		return (ft_strdup(str[0]));
	dup2(pipex->original_stdout, 1);
	fd_printf(2, "%s: command not found\n",
		str[0]);
	return (0);
}

/*
simple extension for get_cmd()
*/
void	get_cmd_loop(t_shell *shell, char *temp, char **command)
{
	temp = ft_strdup(shell->pipex.paths[shell->pipex.cmd_i]);
	if (!temp)
		ft_die(shell, 1, 12);
	ft_free((void **) &shell->pipex.paths[shell->pipex.cmd_i]);
	shell->pipex.paths[shell->pipex.cmd_i] = ft_strjoin(temp, "/");
	if (!shell->pipex.paths[shell->pipex.cmd_i])
		ft_die(shell, 1, 12);
	ft_free((void **) &temp);
	temp = ft_strdup(shell->pipex.paths[shell->pipex.cmd_i]);
	if (!temp)
		ft_die(shell, 1, 12);
	ft_free((void **) &shell->pipex.paths[shell->pipex.cmd_i]);
	shell->pipex.paths[shell->pipex.cmd_i] = ft_strjoin(temp, command[0]);
	if (!shell->pipex.paths[shell->pipex.cmd_i])
		ft_die(shell, 1, 12);
	ft_free((void **) &temp);
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
char	**get_cmd(t_shell *shell, char *str, int id)
{
	char	*temp;
	char	**command;
	char	**temp_parser;

	temp = 0;
	shell->pipex.cmd_i = -1;
	shell->pipex.paths = ft_take_paths(shell, id);
	temp_parser = ft_parser(shell, str, " <");
	command = line_filter(temp_parser);
	ft_free_mat((void ***) &temp_parser);
	while (shell->pipex.paths[++shell->pipex.cmd_i])
		get_cmd_loop(shell, temp, command);
	temp = path_checker(shell, &shell->pipex, command, -1);
	ft_free((void **) &command[0]);
	if (!temp)
		command[0] = 0;
	else
	{
		command[0] = ft_strdup(temp);
		if (!command[0])
			return (0);
		ft_free((void **) &temp);
	}
	ft_free_mat((void ***) &shell->pipex.paths);
	return (command);
}

/*
	int	is_only_red(char *str)

	this func check if the command is composed only
	' ' or '31' character if so return 1 else 0
*/
int	is_only_red(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != 31)
			return (0);
		i++;
	}
	return (1);
}

/*
	void	execute_cmd(t_shell *shell, char **argv, int *child_id)	
 
	this func check if the command is compose of only redirection
	if so exit otherwise it ask for the final command to get_cmd
	and pass it to execve
*/
void	execute_cmd(t_shell *shell, char **argv, int *child_id)
{
	char	**cmd;

	cmd = NULL;
	if (is_only_red(argv[*child_id]))
		ft_exit_exec(shell, argv, cmd, 0);
	ambiguous_red(shell, *child_id, cmd, argv);
	ft_replace(argv[(*child_id)], "\37", ' ');
	cmd = get_cmd(shell, argv[(*child_id)], *child_id);
	if (!cmd)
		ft_exit_exec(shell, argv, cmd, 2);
	if (!cmd[0])
		ft_exit_exec(shell, argv, cmd, 3);
	trim_strs(shell, cmd, "\'");
	trim_strs(shell, cmd, "\"");
	ft_free_mat((void ***) &argv);
	execve(cmd[0], cmd, shell->envp);
}
