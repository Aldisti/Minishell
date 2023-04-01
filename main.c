/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/29 16:03:04 by adi-stef         ###   ########.fr       */
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
	char	*strs[4];

	strs[3] = 0;
	pwd_prompt = getcwd(0, 0);
	strs[0] = "\033[1;36m";
	strs[1] = ft_strrchr(pwd_prompt, '/') + 1;
	strs[2] = "\033[0m\033[1;32m$> \033[0m";
	strs[3] = ft_joiner(strs, 0);
	free(pwd_prompt);
	return (strs[3]);
}

int	main(int ac, char **av, char **envp)
{
	char			*prompt;
	t_shell			shell;

	if (ac != 1)
		return (0);
	(void)av;
	shell.list = ft_env_set(envp);
	ft_shell_set(&shell);
	while (42)
	{
		prompt = ft_prompt();
		shell.line = readline(prompt);
		ft_free((void **)&prompt);
		if (!shell.line)
			exit(169);
		if (!shell.line[0])
			continue ;
		add_history(shell.line);
		shell.parsed = ft_parser(&shell, "|&");
		ft_parser_checks(&shell);
		ft_expand_all(&shell);
		if (!ft_strncmp(shell.parsed[0], "exit", 4))
		{
			clear_history();
			ft_die(&shell, 0, 0);
			exit(1);
		}
		else
			pipex(&shell, shell.parsed);
		// ft_die(&shell, 0, 0);
		ft_free_mat((void ***) &shell.parsed);
		//shell_errno = ft_executor(&shell); 
		//ft_catch_error(&shell);
	}
	return (0);
}
