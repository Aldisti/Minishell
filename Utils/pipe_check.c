/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:52:04 by marco             #+#    #+#             */
/*   Updated: 2023/04/19 14:40:45 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

void	close_everything(t_shell *shell)
{
	char	*str;

	while (shell->pipex.flag > 0)
	{
		str = get_next_line(shell->pipex.original_stdin);
		free(str);
		shell->pipex.flag--;
	}
}

int	special_cat(t_shell *shell, char **cmd, int id)
{
	char	**temp;
	char	**new_cmd;

	temp = ft_parser(shell, cmd[id], " ");
	new_cmd = line_filter(temp);
	ft_free_mat((void ***) &temp);
	if (new_cmd[1] || ft_strncmp(new_cmd[0], "cat", 3)
		|| shell->red.outfiles[id][0]
			|| shell->red.afiles[id][0] || shell->red.infiles[id][0])
	{
		shell->pipex.is_first = 0;
		ft_free_mat((void ***) &new_cmd);
		return (0);
	}
	if (id == 0)
		shell->pipex.is_first = 1;
	ft_free_mat((void ***) &new_cmd);
	return (1);
}

int	pre_check(t_shell *shell, char **cmd, int *id)
{
	sigaction(SIGINT, &shell->a_nothing, 0);
	sigaction(SIGQUIT, &shell->a_nothing, 0);
	if (!ft_strncmp(cmd[*id], "./", 2)
		&& access(ft_strchr(cmd[*id], '/') + 1, F_OK))
		return (g_shell_errno = fd_printf(2, "%s: no such file or directory\n",
				cmd[*id]) * 0 + 127);
	if (!ft_strncmp(cmd[*id], "./", 2)
		&& access(ft_strchr(cmd[*id], '/') + 1, X_OK))
		return (g_shell_errno = fd_printf(2, "%s: permission denied\n",
				cmd[*id]) * 0 + 126);
	while (special_cat(shell, cmd, *id)
		&& (shell->pipex.is_first || (*id) == 0))
	{
		shell->pipex.flag++;
		(*id)++;
	}
	return (0);
}
