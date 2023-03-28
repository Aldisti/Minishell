/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/28 16:49:12 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_shell_errno = 0;

void	ft_print(char **tab)
{
	if (!tab)
		return ;
	for (int i = 0; tab[i]; i++)
		printf("%s\n", tab[i]);
}

char	*ft_prompt(void)
{
	char	*pwd_prompt;
	char	*temp1;
	char	*temp;
	char	*color_pwd;

	pwd_prompt = getcwd(0, 0);
	color_pwd = ft_strjoin("\033[1;36m", ft_strrchr(pwd_prompt, '/') + 1);
	temp1 = ft_strjoin(color_pwd, "\033[0m");
	temp = ft_strjoin(temp1, "\033[1;32m$> \033[0m");
	free(pwd_prompt);
	free(color_pwd);
	free(temp1);
	return (temp);
}

void	ft_handler(int signum)
{
	char	*prompt;

	if (signum == SIGINT)
	{
		prompt = ft_prompt();
		printf("%s\n", prompt);
		free(prompt);
	}
	else
	{
		printf("ciao\n");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell				shell;
	char				*prompt;
	// struct sigaction	action;

	if (ac != 1)
		return (0);
	(void)av;
	shell.list = ft_env_set(envp);
	// action.sa_sigaction = ft_handler;
	// action.sa_flags = SA_SIGINFO | SA_RESTART;
	// sigaction(SIGINT, &action, 0);
	// sigaction(SIGQUIT, &action, 0);
	signal(SIGQUIT, &ft_handler);
	while (42)
	{
		prompt = ft_prompt();
		shell.line = readline(prompt);
		if (!shell.line)
			exit(169);
		free(prompt);
		add_history(shell.line);
		shell.parsed = ft_parser(&shell, "|&");
		shell.parsed = ft_expand_all(&shell);
		if (!ft_strncmp(shell.parsed[0], "cd", 2))
			cd(shell.parsed, envp);
		else if (!ft_strcmp(shell.parsed[0], "exit"))
		{
			rl_clear_history();
			ft_free(shell.parsed);
			exit(1);
		}
		else
			pipex(&shell, shell.parsed);
		ft_free(shell.parsed);
		// shell.parsed = ft_redirection(&shell);
		// shell_errno = ft_executor(&shell);
		// ft_catch_error(&shell);
	}
	return (0);
}