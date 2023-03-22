/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/21 14:55:28 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *pwd_in_prompt()
{
	char	*pwd_prompt;
	char	*temp1;
	char	*temp;
	char	*color_pwd;

	pwd_prompt = pwd();
	color_pwd = ft_strjoin("\033[1;36m", ft_strrchr(pwd_prompt, '/') + 1);
	temp1 = ft_strjoin(color_pwd, "\033[0m");
	temp = ft_strjoin(temp1, "\033[1;32m$> \033[0m");
	free(pwd_prompt);
	free(color_pwd);
	free(temp1);
	return (temp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*tmp;
	char	*pwd_prompt;
	int		i;

	shell = (t_shell *) malloc (sizeof(t_shell));
	if (!shell)
		return (1);
	while (42)
	{
		pwd_prompt = pwd_in_prompt();
		shell->line = readline(pwd_prompt);
		free(pwd_prompt);
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
		free(shell->parsed);
		usleep(1000);
	}
	return (0);
}
