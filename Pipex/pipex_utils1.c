/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:37:43 by marco             #+#    #+#             */
/*   Updated: 2023/03/29 10:26:00 by mpaterno         ###   ########.fr       */
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
		if (!temp)
			exit(1);//ft_die
		ft_free((void **) &strs[i]);
		strs[i] = ft_strdup(temp);
		if (!strs[i])
			exit(1);//ft_die
		ft_free((void **) &temp);
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

void	trim_strs(char **strs, const char *set)
{
	char	*temp;
	int		i;

	i = -1;
	while (strs[++i])
	{
		if (!ft_strncmp(strs[i], set, 1))
		{
			temp = ft_strtrim(strs[i], set);
			if (!temp)
				exit(7);//ft_die
			ft_free((void **) &strs[i]);
			strs[i] = ft_strdup(temp);
			if (!strs[i])
				exit(8);//ft_die
			ft_free((void **) &temp);
		}
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
	else if (mode == 1 && id > 0)
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
