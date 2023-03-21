/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:37:43 by marco             #+#    #+#             */
/*   Updated: 2023/03/21 12:11:54 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
}

void	child_free(t_pipex *pipex, char **cmd)
{
	int	i;

	i = -1;
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	while (cmd && cmd[++i])
		free(cmd[i]);
	if (cmd)
		free(cmd);
	free(pipex->pipe);
	free(pipex->pid);
	close(pipex->original_stdout);
}

int	create_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->cmd_count)
	{
		if (pipe(pipex->pipe + 2 * i) == -1)
			return (-1);
	}
	return (1);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->pipe_count)
		close(pipex->pipe[i]);
}

void	my_dup(int first, int second)
{
	dup2(first, 0);
	dup2(second, 1);
}
