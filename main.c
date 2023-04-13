/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/13 11:39:31 by adi-stef         ###   ########.fr       */
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
	while (strs[i])
		printf("-%s-\n", strs[i++]);
}

char	*ft_prompt(void)
{
	char	*pwd_prompt;
	char	*strs[4];

	strs[3] = 0;
	pwd_prompt = getcwd(0, 0);
	if (!pwd_prompt)
		return (NULL);
	if (g_shell_errno)
		strs[0] = "\033[1;31m";
	else
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
	char	*line;

	line = NULL;
	prompt = ft_prompt();
	if (!prompt)
		ft_die(shell, 1, 1);
	line = ft_readline(prompt);
	ft_replace(line, " \n\t", ' ');
	shell->line = ft_strtrim(line, " ");
	ft_free((void **) &line);
	ft_free((void **) &prompt);
	if (!shell->line)
		ft_die(shell, 1, 0);
}

char	**ft_parsed_set(t_shell *shell)
{
	shell->parsed = ft_parser(shell, shell->line, "|&");
	if (!shell->parsed)
		return (NULL);
	shell->parsed = ft_parser_checks(shell);
	return (shell->parsed);
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
		shell.parsed = ft_parsed_set(&shell);
		if (!shell.parsed)
			continue ;
		ft_expand_all(&shell, shell.parsed);
		ft_lvls(&shell);
		if (ft_redirection(&shell))
			continue ;
		pipex(&shell, shell.parsed);
		ft_free_routine(&shell);
	}
	return (0);
}
