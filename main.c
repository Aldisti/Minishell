/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/20 21:55:00 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*tmp;
	char	*pwd_prompt;
	char	*pwd_temp;
	int		i;

	shell = (t_shell *) malloc (sizeof(t_shell));
	if (!shell)
		return (1);
	while (42)
	{
		pwd_temp = pwd();
		pwd_prompt = ft_strjoin(pwd_temp, "\033[1;36m$> \033[0m");
		shell->line = readline(pwd_prompt);
		add_history(shell->line);
		if (!strcmp(shell->line, "exit"))
		{
			printf("exit\n");
			clear_history();
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
		free(shell->line);
		if (!shell->parsed)
		{
			perror("Error\n[parsed] not allocated\n");
			break ;
		}
		if (!ft_strncmp(shell->parsed[0], "pwd", 3))
			print_pwd();
		else if (!ft_strncmp(shell->parsed[0], "cd", 2) && ft_strlen(shell->parsed[0]) == 2)
			cd(shell->parsed, envp);
		else
			pipex(shell->parsed);
		// ft_executor(...);
		i = 0;
		while (shell->parsed[i])
		{
			//printf("%s\e[30;47m%%\e[0m\n", shell->parsed[i]);
			free(shell->parsed[i]);
			i++;
		}
		free(pwd_prompt);
		free(pwd_temp);
		free(shell->parsed);
		usleep(1000);
	}
	return (0);
}
