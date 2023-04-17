/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:45:46 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/15 14:46:53 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

extern int	g_shell_errno;

void	ft_does_nothing(int signum)
{
	(void)signum;
	return ;
}

void	ft_handle_int(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_shell_errno = 130;
}

void	ft_handle_quit(int signum)
{
	if (signum != SIGQUIT)
		return ;
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signals_set(t_shell *shell)
{
	tcgetattr(STDIN_FILENO, &shell->tty_attrs);
	shell->tty_attrs.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->tty_attrs);
	shell->a_nothing.sa_handler = ft_does_nothing;
	shell->a_int.sa_handler = ft_handle_int;
	shell->a_quit.sa_handler = ft_handle_quit;
	shell->a_nothing.sa_flags = SA_RESTART;
	shell->a_int.sa_flags = SA_RESTART;
	shell->a_quit.sa_flags = SA_RESTART;
	sigemptyset(&(shell->a_nothing.sa_mask));
	sigemptyset(&(shell->a_int.sa_mask));
	sigemptyset(&(shell->a_quit.sa_mask));
	sigaction(SIGINT, &shell->a_int, 0);
	sigaction(SIGQUIT, &shell->a_quit, 0);
}
