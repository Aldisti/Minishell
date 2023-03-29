/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:45:46 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/29 16:03:20 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signals_set(t_shell *shell)
{
	tcgetattr(STDIN_FILENO, &shell->tty_attrs);
	shell->tty_attrs.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->tty_attrs);
	shell->action_nothing.sa_handler = ft_does_nothing;
	shell->action_nothing.sa_flags = SA_RESTART;
	shell->action_int.sa_handler = ft_handle_int;
	shell->action_int.sa_flags = SA_RESTART;
	shell->action_quit.sa_handler = ft_handle_quit;
	shell->action_quit.sa_flags = SA_RESTART;
}