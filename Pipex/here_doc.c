/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 22:49:01 by marco             #+#    #+#             */
/*   Updated: 2023/03/27 22:49:17 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	here_doc(t_pipex *pipex, char *limiter)
{
	char	*temp;
	int		file;

	file = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (42)
	{
		write(pipex->original_stdout, "heredoc> ", 9);
		temp = get_next_line(pipex->infile_fd);
		if (!temp || (!ft_strncmp(temp, limiter, ft_strlen(limiter))
				&& ft_strlen(temp) == ft_strlen(limiter) + 1))
			break ;
		write(file, temp, ft_strlen(temp));
		free(temp);
	}
	close(file);
	if (temp)
		free(temp);
	return (open(".here_doc", O_RDWR));
}

void	cat_here_doc(t_pipex *pipex, char *limiter)
{
	int		i;
	char	*temp;

	i = here_doc(pipex, limiter);
	temp = get_next_line(i);
	while (temp)
	{
		write(1, temp, ft_strlen(temp));
		free(temp);
		temp = get_next_line(i);
	}
	free(temp);
	close(i);
	unlink(".here_doc");
}
