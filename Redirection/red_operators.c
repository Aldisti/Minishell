/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_operators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:47:14 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/15 19:35:39 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_shell_errno;

int	ft_input_red(t_shell *shell, int n_cmd, int *ind)
{
	if (shell->parsed[n_cmd][*ind] == '<'
		&& !ft_in(shell->parsed[n_cmd][*ind + 1], "><"))
	{
		shell->red.fdin[n_cmd / 2] = ft_get_fd(shell, n_cmd,
				*ind, 'i');
		while (ft_in(shell->parsed[n_cmd][*ind], "><"))
			(*ind)++;
		if (ft_get_filename(shell, n_cmd, ind, 'i'))
			ft_die(shell, 1, 12);
		if (ft_remove_quotes(shell, &shell->red.infiles[n_cmd / 2]))
			ft_die(shell, 1, 12);
		if (access(shell->red.infiles[n_cmd / 2], F_OK | R_OK)
			|| !ft_intab(shell->red.infiles[n_cmd / 2],
				shell->files))
		{
			g_shell_errno = 1;
			return (2);
		}
	}
	return (0);
}

int	ft_output_red(t_shell *shell, int n_cmd, int *ind)
{
	int	fd;

	if (shell->parsed[n_cmd][*ind] == '>'
		&& !ft_in(shell->parsed[n_cmd][*ind + 1], "><"))
	{
		shell->red.fdout[n_cmd / 2] = ft_get_fd(shell, n_cmd,
				*ind, 'o');
		while (ft_in(shell->parsed[n_cmd][*ind], "><"))
			(*ind)++;
		if (ft_get_filename(shell, n_cmd, ind, 'o'))
			ft_die(shell, 1, 12);
		if (ft_remove_quotes(shell, &shell->red.outfiles[n_cmd / 2]))
			ft_die(shell, 1, 12);
		ft_free((void **) &shell->red.afiles[n_cmd / 2]);
		fd = open(shell->red.outfiles[n_cmd / 2],
				O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
			ft_die(shell, 1, 12);
		close(fd);
	}
	return (0);
}

int	ft_append_red(t_shell *shell, int n_cmd, int *ind)
{
	int	fd;

	if (shell->parsed[n_cmd][*ind] == '>'
		&& shell->parsed[n_cmd][*ind + 1] == '>')
	{
		shell->red.fda[n_cmd / 2] = ft_get_fd(shell, n_cmd,
				*ind, 'a');
		while (ft_in(shell->parsed[n_cmd][*ind], "><"))
			(*ind)++;
		if (ft_get_filename(shell, n_cmd, ind, 'a'))
			ft_die(shell, 1, 12);
		if (ft_remove_quotes(shell, &shell->red.afiles[n_cmd / 2]))
			ft_die(shell, 1, 12);
		ft_free((void **) &shell->red.outfiles[n_cmd / 2]);
		fd = open(shell->red.afiles[n_cmd / 2],
				O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
			ft_die(shell, 1, 12);
		close(fd);
	}
	return (0);
}

int	ft_here_doc(t_shell *shell, char *limiter)
{
	char	*temp;
	int		file;

	file = open(".here_doc",
			O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (file == -1)
		ft_die(shell, 1, 12);
	while (42)
	{
		write(1, "heredoc> ", 9);
		temp = get_next_line(0);
		if (!temp || (!ft_strncmp(temp, limiter, ft_strlen(limiter))
				&& ft_strlen(temp) == ft_strlen(limiter) + 1))
			break ;
		write(file, temp, ft_strlen(temp));
		free(temp);
	}
	close(file);
	if (temp)
		free(temp);
	return (0);
}

int	ft_hdoc_red(t_shell *shell, int n_cmd, int *ind)
{
	if (shell->parsed[n_cmd][*ind] == '<'
		&& shell->parsed[n_cmd][*ind + 1] == '<')
	{
		shell->red.fdin[n_cmd / 2] = ft_get_fd(shell, n_cmd,
				*ind, 'h');
		while (ft_in(shell->parsed[n_cmd][*ind], "><"))
			(*ind)++;
		if (ft_get_filename(shell, n_cmd, ind, 'h'))
			ft_die(shell, 1, 12);
		if (ft_remove_quotes(shell, &shell->red.infiles[n_cmd / 2]))
			ft_die(shell, 1, 12);
		if (ft_here_doc(shell, shell->red.infiles[n_cmd / 2]))
			ft_die(shell, 1, 12);
		ft_free((void **) &shell->red.infiles[n_cmd / 2]);
		shell->red.infiles[n_cmd / 2] = ft_strdup(".here_doc");
		if (!shell->red.infiles[n_cmd / 2])
			ft_die(shell, 1, 12);
	}
	return (0);
}
