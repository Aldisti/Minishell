/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:16:34 by marco             #+#    #+#             */
/*   Updated: 2023/04/05 14:21:59 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void    my_redir(t_shell *shell, int id)
{
	int	fd;

	fd = open(shell->red.infiles[id], O_RDONLY);
	dup2(fd, 0);
	close(fd);
	fd = open(shell->red.outfiles[id], O_RDONLY);
	dup2(fd, 1);
	close(fd);
	fd = open(shell->red.infiles[id], O_RDONLY);
	dup2(fd, 0);
	close(fd);
}