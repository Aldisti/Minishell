/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:52:04 by marco             #+#    #+#             */
/*   Updated: 2023/04/20 14:09:46 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

void	built_in_check(t_shell *shell, int *id, char **cmd, int *fd)
{
	dup2(shell->pipex.temp_flag, 0);
	close(shell->pipex.temp_flag);
	if ((*id) != shell->pipex.cmd_count - 1)
		dup2(fd[1], 1);
	if (shell->red.outfiles[*id][0])
		red_selector(shell, *id, 2);
	if (shell->red.afiles[*id][0])
		red_selector(shell, *id, 0);
	if (shell->red.infiles[*id][0])
		red_selector(shell, *id, 1);
	close(fd[1]);
	ft_replace(cmd[*id], "\37", ' ');
	execute_built_in(shell, cmd, shell->lvls[*id], *id);
	shell->pipex.temp_flag = fd[0];
	dup2(shell->pipex.original_stdout, 1);
	dup2(shell->pipex.original_stdin, 0);
}

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

	if (shell->pipex.cmd_count == 1 || id == shell->pipex.cmd_count - 1)
		return (0);
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
	return (0);
}
