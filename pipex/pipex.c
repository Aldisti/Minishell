/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:31:08 by mpaterno          #+#    #+#             */
/*   Updated: 2023/03/21 12:18:33 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_proc(t_pipex *pipex, char **argv, int child_id)
{
	char	**cmd;

	pipex->pid[child_id] = fork();
	if (pipex->pid[child_id] < 0)
		return (-1);
	if (pipex->pid[child_id] == 0)
	{
		if (child_id == 0 && pipex->cmd_count != 1)
			my_dup(pipex->infile_fd, pipex->pipe[2 * child_id + 1]);
		else if (child_id == pipex->cmd_count - 1)
			my_dup(pipex->pipe[2 * child_id - 2], pipex->outfile_fd);
		else
			my_dup(pipex->pipe[2 * child_id - 2],
				pipex->pipe[2 * child_id + 1]);
		close_pipes(pipex);
		cmd = get_cmd(pipex, argv, child_id);
		if (!cmd[0])
		{
			child_free(pipex, cmd);
			exit(0);
		}
		execve(cmd[0], cmd, 0);
	}
	return (1);
}

int	pipex_init(t_pipex *pipex, int argc, char **argv)
{
	pipex->original_stdout = dup(1);
	pipex->cmd_count = (argc);
	pipex->pipe_count = 2 * (pipex->cmd_count - 1);
	pipex->pipe = (int *)malloc(sizeof(int) * (pipex->pipe_count));
	pipex->pid = (pid_t *) malloc(sizeof(pid_t) * pipex->cmd_count);
	if (create_pipes(pipex) == -1)
		return (-1);
	// pipex->infile_fd = open(argv[1], O_RDONLY);
	// pipex->outfile_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0777);
	pipex->infile_fd = dup(0);
	pipex->outfile_fd = dup(1);
	if (pipex->infile_fd < 0)
	{
		printf("%s: %s: file o directory inesistente\n", argv[1], argv[2]);
		close_pipes(pipex);
		child_free(pipex, 0);
		return (-1);
	}
	return (1);
}

int	pipex(char **argv)
{
	t_pipex	pipex;
	char	*temp;
	int		argc;
	int		i;

	i = -1;
	// if (argc < 3)
	// 	return (0);
	
	while (argv[++i])
	{
		temp = ft_strtrim(argv[i], "\"");
		free(argv[i]);
		argv[i] = ft_strdup(temp);
	}
	argc = i;
	i = -1;
	if (pipex_init(&pipex, argc, argv) == -1)
		return (1);
	while (++i < pipex.cmd_count)
	{
		if (child_proc(&pipex, argv, i) < 0)
			return (3);
	}
	close_pipes(&pipex);
	i = -1;
	while (++i < pipex.cmd_count)
		waitpid(pipex.pid[i], 0, 0);
	child_free(&pipex, 0);
	return (0);
}