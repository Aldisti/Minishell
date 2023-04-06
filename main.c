/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/06 15:41:41 by gpanico          ###   ########.fr       */
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
	pwd_prompt = getcwd(0, 0);
	strs[0] = "\033[1;36m";
	strs[1] = ft_strrchr(pwd_prompt, '/') + 1;
	strs[2] = "\033[0m\033[1;32m$> \033[0m";
	strs[3] = ft_joiner(strs, 0);
	ft_free((void **)&pwd_prompt);
	return (strs[3]);
}

int	ft_end_with(char *line, char end)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (line[i] == '|' && !found)
			found = 1;
		else if (found && !ft_in(line[i], " \t\n"))
			found  = 0;
		i++;
	}
	return (found);
}

char	*ft_read_again(char *prompt)
{
	char	*tmp;
	char	*line;

	tmp = readline("> ");
	if (!tmp)
		return (NULL);
	line = ft_strjoin(" ", tmp);
	ft_free((void **) &tmp);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_readline(char *prompt)
{
	char	**lines;
	char	*line;
	int	dim;

	lines = NULL;
	dim = 2;
	lines = (char **) ft_realloc(lines, sizeof(char *), 0, dim);
	if (!lines)
		return (NULL); //ft_die(); Error: memory error
	lines[dim - 2] = readline(prompt);
	if (!lines[dim - 2])
		return (NULL); //ft_die(); Error: memory error
	while (ft_end_with(lines[dim - 2], '|'))
	{
		lines = (char **) ft_realloc(lines, sizeof(char *), dim, dim + 1);
		if (!lines)
			return (NULL); //ft_die(); Error: memory error
		dim++;
		lines[dim - 2] = ft_read_again("> ");
		if (!lines[dim - 2])
			return (NULL); //ft_die(); Error: memory error
	}
	line = ft_joiner(lines, 1);
	free(lines);
	return (line);
}

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
	while (42)
	{
		prompt = ft_prompt();
		shell.line = ft_readline(prompt);
		ft_replace(shell.line, " \n\t", ' ');
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
			return(ft_die(&shell, 0, 0));
		else
			pipex(&shell, shell.parsed);
		ft_free_routine(&shell);
	}
	return (0);
}
