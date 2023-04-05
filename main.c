/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/05 15:52:08 by adi-stef         ###   ########.fr       */
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
	char	**cmd;
	int		i;

	if (ac != 1)
		return (0);
	(void)av;
	shell.list = ft_env_set(envp);
	ft_shell_set(&shell);
	// my_print(shell.envp);
	// printf("name: %s\nvalue: %s\n", shell.list->content->name, shell.list->content->value);
	// exit(1);
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

		// i = write(1, "lvls: ", 6) * 0;
		// while (i < shell.n_cmds)
		// 	printf("%d|", shell.lvls[i++]);
		// printf("\n");
		prompt = ft_strtrim(shell.parsed[0], " ");
		ft_free((void **)&shell.parsed[0]);
		shell.parsed[0] = prompt;
		prompt = ft_strtrim(shell.parsed[1], " ");
		ft_free((void **)&shell.parsed[1]);
		shell.parsed[1] = prompt;
		// printf("cmd: |%s|\n", shell.parsed[0]);
	
		if (!ft_strncmp(shell.parsed[0], "exit", 4))
			return(ft_die(&shell, 0, 0));
		else if (!ft_strncmp(shell.parsed[0], "export", 6))
		{
			cmd = ft_split(shell.parsed[0], 32);
			g_shell_errno = ft_export(&shell, cmd, shell.lvls[0]);
			ft_free_mat((void ***)&cmd);
		}
		else
			pipex(&shell, shell.parsed);
		ft_free_routine(&shell);
		//shell_errno = ft_executor(&shell); 
		//ft_catch_error(&shell);
	}
	return (0);
}
