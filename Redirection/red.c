/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:46:38 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/12 08:10:01 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirection(t_shell *shell)
{
	int	i;
	int	ret;

	if (ft_allocate_rarray(shell))
		ft_die(shell, 1, 12);
	i = -1;
	while (shell->parsed[++i])
		if (ft_red_check(shell->parsed[i]))
			return (ft_die(shell, 0, 258));
	i = 0;
	while (shell->parsed[i])
	{
		ret = ft_apply_red(shell, i);
		if (ret == 1)
			ft_die(shell, 1, 12);
		else if (ret == 2 && ++i)
			continue ;
		ft_replace_red(shell, i);
		i++;
	}
	if (ft_fill_red(shell))
		ft_die(shell, 1, 12);
	return (0);
}
