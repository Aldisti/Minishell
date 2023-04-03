/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/03 07:39:29 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_shell_errno = 0;

void	my_print(char **strs)
{
	int i = -1;

	while(strs[++i])
		printf("%s\n", strs[i]);
}

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

int	main(int ac, char **av, char **envp)
{
	char			*prompt;
	t_shell			shell;

	if (ac != 1)
		return (0);
	(void)av;
	shell.list = ft_env_set(envp);
	ft_signals_set(&shell);
	sigaction(SIGINT, &shell.action_int, 0);
	sigaction(SIGQUIT, &shell.action_quit, 0);
	shell.envp = list_convert(shell.list);
	shell.line = NULL;
	while (42)
	{
		prompt = ft_prompt();
		shell.line = readline(prompt);
		if (!shell.line)
			exit(169);
		if (!shell.line[0])
			continue ;
		free(prompt);
		add_history(shell.line);
		shell.parsed = ft_parser(&shell, shell.line, "|&");
		ft_parser_checks(&shell);
		shell.parsed = ft_expand_all(&shell);
		ft_lvls(&shell);
		ft_redirection(&shell);
		if (!ft_strncmp(shell.parsed[0], "exit", 4))
		{
			clear_history();
			ft_free_mat((void ***) &shell.parsed);
			exit(1);
		}
		else
			pipex(&shell, shell.parsed);
		//ft_free_mat((void ***) &shell.parsed);
		//shell_errno = ft_executor(&shell);
		//ft_catch_error(&shell);
	}
	return (0);
}
