/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:46:38 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/21 15:01:29 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_dollars(t_shell *shell, int *i)
{
	int	j;

	j = 0;
	while (shell->parsed[*i][j])
	{
		if (shell->parsed[*i][j] == '<' && shell->parsed[*i][j + 1] == '<')
			while (shell->parsed[*i][++j] && shell->parsed[*i][j - 1] != 36)
				;
		while (shell->parsed[*i][j] && !ft_in(shell->parsed[*i][j], "<>"))
			j++;
		while (shell->parsed[*i][j] && ft_in(shell->parsed[*i][j], "<>"))
			j++;
		while (ft_in(shell->parsed[*i][j], " "))
			j++;
		if (shell->parsed[*i][j] == '$' && shell->parsed[*i][j + 1]
				&& shell->parsed[*i][j + 1] != ' ')
		{
			ft_get_filename(shell, *i, &j, 'i');
			(*i)++;
			return (1);
		}
		if (j < (int)ft_strlen(shell->parsed[*i]) && !shell->parsed[*i][j])
			j++;
	}
	return (0);
}	

int	ft_redirection(t_shell *shell)
{
	int	i;
	int	ret;

	ft_allocate_rarray(shell);
	i = -1;
	while (shell->parsed[++i])
		if (ft_red_check(shell, shell->parsed[i]))
			return (1);
	i = 0;
	while (shell->parsed[i])
	{
		if (ft_check_dollars(shell, &i))
			continue ;
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
