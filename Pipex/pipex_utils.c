/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:37:43 by marco             #+#    #+#             */
/*   Updated: 2023/03/23 16:06:51 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
int	prepare_strs(char **strs)
char	**strs: already properly setted variable that contain the complete
				command retrived from the shell formatted as follow
				{"path/command", "other option or flag", ...}

this function loop trought all the string contained in strs and trim
the starting and trailing blank space
*/

int	prepare_strs(char **strs)
{
	int		i;
	char	*temp;

	i = -1;
	while (strs[++i])
	{
		temp = ft_strtrim(strs[i], " ");
		free(strs[i]);
		strs[i] = ft_strdup(temp);
		free(temp);
	}
	return (i);
}

/*
int	prepare_strs(char **strs)
char	**strs: already properly setted variable that contain the complete
				command retrived from the shell formatted as follow
				{"path/command", "other option or flag", ...}

this function loop trought all the string contained in strs and trim
the starting and trailing ["] or [']
*/

void	trim_strs(char **strs)
{
	char	*temp;
	int		i;

	i = -1;
	while (strs[++i])
	{
		temp = ft_strtrim(strs[i], "\"\'");
		free(strs[i]);
		strs[i] = ft_strdup(temp);
		free(temp);
	}
}

/*
SELF EXPLANATORY
*/

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->pipe_count)
		close(pipex->pipe[i]);
}

/*
SELF EXPLANATORY
*/

void	my_dup(t_pipex *pipex, int id, int mode)
{
	if (mode == 0)
	{
		dup2(pipex->infile_fd, 0);
		dup2(pipex->pipe[2 * id + 1], 1);
	}
	else if (mode == 1)
	{
		dup2(pipex->pipe[2 * id - 2], 0);
		dup2(pipex->outfile_fd, 1);
	}
	else if (mode == 2)
	{
		dup2(pipex->pipe[2 * id - 2], 0);
		dup2(pipex->pipe[2 * id + 1], 1);
	}
}

/*
SELF EXPLANATORY
*/

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
