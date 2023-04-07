/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/07 08:05:06 by gpanico          ###   ########.fr       */
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
		printf("-%s-\n", strs[i++]);
}

char	*ft_prompt(void)
{
	char	*pwd_prompt;
	char	*strs[4];

	strs[3] = 0;
	pwd_prompt = getcwd(NULL, 0);
	if (!pwd_prompt)
		return (NULL);
	strs[0] = "\033[1;36m";
	strs[1] = ft_strrchr(pwd_prompt, '/') + 1;
	strs[2] = "\033[0m\033[1;32m$> \033[0m";
	strs[3] = ft_joiner(strs, 0);
	ft_free((void **)&pwd_prompt);
	return (strs[3]);
}

void	ft_line_set(t_shell *shell)
{
	char	*prompt;

	prompt = ft_prompt();
	if (!prompt)
		ft_die(shell, 1, 1);
	shell->line = ft_readline(prompt);
	ft_replace(shell->line, " \n\t", ' ');
	ft_free((void **) &prompt);
	if (!shell->line)
		ft_die(shell, 1, 1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1)
		return (0);
	(void)av;
	shell.list = ft_env_set(envp);
	ft_shell_set(&shell);
	while (42)
	{
		ft_line_set(&shell);
		if (!shell.line[0])
			continue ;
		add_history(shell.line);
		shell.parsed = ft_parser(&shell, shell.line, "|&");
		ft_parser_checks(&shell);
		ft_expand_all(&shell);
		ft_lvls(&shell);
		ft_redirection(&shell);
		if (!ft_strncmp(shell.parsed[0], "exit", 4))
			return(ft_die(&shell, 0, 0));
		else
			pipex(&shell, shell.parsed);
		ft_free_routine(&shell);
	}
	return (0);
}
