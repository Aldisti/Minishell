/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c	                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/18 16:40:14 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	main(void)
{
	t_shell	*shell;
	char	*tmp;
	int		i;

	shell = (t_shell *) malloc (sizeof(t_shell));
	if (!shell)
		return (1);
	while (42)
	{
		shell->line = readline("\033[1;36m$> \033[0m");
		add_history(shell->line);
		if (!ft_strncmp(shell->line, "exit", ft_strlen("exit")))
		{
			printf("exit\n");
			rl_clear_history();
			free(shell->line);
			free(shell);
			break ;
		}
		else if (!ft_strncmp(shell->line, "getenv", 6))
		{
			tmp = getenv(shell->line + 7);
			printf("%s\n", tmp);
			free(shell->line);
			continue ;
		}
		shell->parsed = ft_parser(shell->line);
		if (!shell->parsed)
		{
			perror("Error\n[parsed] not allocated\n");
			break ;
		}
		i = ft_executor(shell->parsed);
		if (!i)
			return (write(2, "Error\nfailed to execute cmd\n", 28) * 0 + 1);
		free(shell->line);
	}
	return (0);
}
