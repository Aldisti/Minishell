/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 09:43:03 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/05 22:22:05 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

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
	close(pipex->original_stdin);
	close(pipex->original_stdout);
	while (cmd && cmd[++i])
		ft_free((void **) &cmd[i]);
	if (cmd)
		ft_free((void **) &cmd);
	ft_free((void **) &pipex->pipe);
	ft_free((void **) &pipex->pid);
	pipex->pipe = 0;
	pipex->pid = 0;
	cmd = 0;
}
