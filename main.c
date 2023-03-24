/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/24 11:42:26 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_shell_errno = 0;

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
	t_shell	shell;
	char	*prompt;

	if (ac != 1)
		return (0);
	(void)av;
	// ft_init(&shell, envp);
	while (42)
	{
		prompt = ft_prompt();
		shell.line = readline(prompt);
		free(prompt);
		add_history(shell.line);
		shell.parsed = ft_parser(&shell, "|&");
		// for (int i = 0; shell.parsed[i]; i++)
		// 	printf("%s\n", shell.parsed[i]);
		shell.parsed = ft_expansion(&shell);
		// shell.parsed = ft_redirection(&shell);
		// shell_errno = ft_executor(&shell);
		// ft_catch_error(&shell);
	}
	return (0);
}