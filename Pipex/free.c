/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:43:03 by mpaterno          #+#    #+#             */
/*   Updated: 2023/03/23 16:27:36 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

/*
void	ft_free(char **strs)
char	**strs: doppio puntatore del quale bisogna fare il free

effetua il free di un doppio puntatore a carattere e lo setta a 0
*/
void	ft_free(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		free(strs[i]);
	free(strs);
	strs = 0;
}

/*
void	child_free(t_pipex *pipex, char **cmd)
t_pipex	*pipex: a pointer to pipex struct
char	**cmd: the allocated command to free

this function free and sett all the allocated variablesto 0
and close all the fd including the original stdout
*/

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
	pipex->pipe = 0;
	pipex->pid = 0;
	cmd = 0;
	close(pipex->original_stdout);
}
