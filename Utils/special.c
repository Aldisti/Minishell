/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:58:30 by marco             #+#    #+#             */
/*   Updated: 2023/04/17 22:13:08 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	the_special_one2(t_shell *shell, char **cmd, int id)
{
	char	*str;

	if (!ft_strncmp(ft_strrchr(cmd[0], '/') + 1, "cat", 3) && !cmd[1]
		&& !shell->red.infiles[id][0] && !shell->red.afiles[id][0]
			&& !shell->red.outfiles[id][0])
	{
		str = get_next_line(shell->pipex.original_stdin);
		free(str);
		ft_die(shell, 1, 0);
	}
}

void	the_special_one1(t_shell *shell, int id, char **cmd)
{
	if (id > 0 && ft_strncmp("cat", cmd[id], 3) && !ft_strncmp("cat",
			cmd[id - 1], 3))
		waitpid(shell->pipex.pid[id - 1], 0, 0);
}
