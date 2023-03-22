/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:56:40 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/21 11:06:33 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_shell *env, char **envp);
char	**ft_parser(t_shell *shell, char *set);
char	**ft_expansion(t_shell *shell);
char	**ft_redirection(t_shell *shell);
int		ft_executor(t_shell *shell);
void	ft_catch_error(t_shell *shell);

int	main(int ac, void **av, char **envp)
{
	t_shell	shell;

	if (ac != 1)
		return (0);
	(void)av;
	ft_init(&shell, envp);
	while (42)
	{
		shell->line = readline("\033[1;36m$> \033[0m");
		add_history(shell->line);
		shell.parsed = ft_parser(&shell, "|&");
		shell.parsed = ft_expansion(&shell);
		shell.parsed = ft_redirection(&shell);
		shell_errno = ft_executor(&shell);
		ft_catch_error(&shell);
	}
	return (0);
}
