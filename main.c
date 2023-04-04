/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/04 11:15:40 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_shell_errno = 0;

void	my_print(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while(strs[i])
		printf("%s\n", strs[i++]);
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
	ft_free((void **)&pwd_prompt);
	return (strs[3]);
}

int	ft_export(t_shell *shell, char **cmd, int lvl);

int	main(int ac, char **av, char **envp)
{
	char	*prompt;
	t_shell	shell;
	char	*cmd[] = {"export", "HOME"};

	if (ac != 1)
		return (0);
	(void)av;
	shell.list = ft_env_set(envp);
	ft_shell_set(&shell);
	ft_export(&shell, cmd, 0);
	ft_die(&shell, 0, 0);
	exit(0);
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
		shell.parsed = ft_parser(&shell, shell.line, "|&");
		ft_parser_checks(&shell);
		ft_expand_all(&shell);
		ft_lvls(&shell);
		ft_redirection(&shell);
		if (!ft_strncmp(shell.parsed[0], "exit", 4))
			return(0);
		else
			pipex(&shell, shell.parsed);
		// ft_die(&shell, 0, 0);
		ft_free_mat((void ***) &shell.parsed);
		//shell_errno = ft_executor(&shell); 
		//ft_catch_error(&shell);
	}
	return (0);
}
