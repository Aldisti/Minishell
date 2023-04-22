/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/22 15:43:58 by adi-stef         ###   ########.fr       */
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

char	*ft_prompt(t_shell *shell)
{
	char	*pwd_prompt;
	char	*strs[4];

	strs[3] = 0;
	errno = 0;
	pwd_prompt = getcwd(0, 0);
	if (!pwd_prompt && errno == 2)
		pwd_prompt = ft_strdup(ft_get_env(ft_get_node(shell->list,
						"PWD"), 0)->value);
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
	prompt = ft_prompt(shell);
	if (!prompt)
		ft_die(shell, 1, 1);
	line = ft_readline(prompt);
	ft_replace(line, " \n\t\v", ' ');
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
		ft_free_routine(&shell);
		ft_line_set(&shell);
		if (ft_continue(&shell, 1))
			continue ;
		add_history(shell.line);
		shell.parsed = ft_parsed_set(&shell);
		if (ft_continue(&shell, 2))
			continue ;
		ft_lvls(&shell);
		ft_expand_all(&shell, shell.parsed, -1);
		if (ft_continue(&shell, 3) || ft_redirection(&shell))
			continue ;
		ft_while(&shell);
	}
	return (0);
}
