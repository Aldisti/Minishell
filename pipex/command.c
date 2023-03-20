/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:41:00 by marco             #+#    #+#             */
/*   Updated: 2023/03/20 16:09:56 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_not_found(t_pipex *pipex)
{
	dup2(pipex->original_stdout, 1);
	printf("%s: comando non trovato\n", ft_strrchr(pipex->paths[0], '/') + 1);
	free(pipex->paths);
	child_free(pipex, 0);
	close(pipex->original_stdout);
	exit(1);
}

char	*path_checker(t_pipex *pipex)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	while (pipex->paths[++i] != 0)
	{
		if (!access(pipex->paths[i], 0))
		{
			flag = 1;
			break ;
		}	
	}
	if (flag)
		return (pipex->paths[i]);
	else
		command_not_found(pipex);
	return (0);
}

char	**path_n_command(t_pipex *pipex, char **argv, int el)
{
	char	*temp;
	char	**command;

	pipex->cmd_i = -1;
	command = ft_split(argv[el], ' ');
	while (pipex->paths[++pipex->cmd_i])
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
	free(command[0]);
	temp = path_checker(pipex);
	if (!temp)
		command[0] = 0;
	else
		command[0] = ft_strdup(temp);
	ft_free(pipex->paths);
	return (command);
}

char	**get_cmd(t_pipex *pipex, char **argv, int child_id)
{
	char	**temp;

	pipex->paths = ft_split(getenv("PATH"), ':');
	protect_space(argv[child_id]);
	temp = path_n_command(pipex, argv, child_id);
	convert(temp);
	r_trim(temp);
	return (temp);
}
