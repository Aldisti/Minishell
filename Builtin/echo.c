/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afraccal <afraccal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:47:55 by afraccal          #+#    #+#             */
/*   Updated: 2023/03/24 15:16:51 by afraccal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->parsed[i + 1] && !ft_strncmp(shell->parsed[i + 1], "-n", 3))
		i++;
	while (shell->parsed[++i])
	{
		printf("%s", shell->parsed[i]);
		if (shell->parsed[i + 1])
			write(1, " ", 1);
	}
	if(shell->parsed[1] || ft_strncmp(shell->parsed[1], "-n", 2))
		write(1, "\n", 1);
	shell->word = ft_strdup("");
	free(shell->exit_code);
	shell->exit_code = strdup("0");
}