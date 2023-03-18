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
		if (!strcmp(shell->line, "exit"))
		{
			printf("exit\n");
			rl_clear_history();
			free(shell->line);
			free(shell);
			break ;
		}
		else if (!strncmp(shell->line, "getenv", 6))
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
		ft_executor(ft_getcmd(shell->parsed));
		i = 0;
		while (shell->parsed[i])
		{
			printf("%s\e[30;47m%%\e[0m\n", shell->parsed[i]);
			free(shell->parsed[i]);
			i++;
		}
		free(shell->line);
		free(shell->parsed);
	}
	return (0);
}
