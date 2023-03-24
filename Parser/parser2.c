/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:05:56 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/24 09:06:14 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_parser(t_shell *shell, char *set)
{
	int		dim;
	int		i;
	char	**parsed;

	parsed = (char **)ft_calloc(sizeof(char *), 1);
	if (!parsed)
		exit(1); // ft_die(); Error: memory error
	dim = 1;
	i = 0;
	while (shell->line[i])
	{
		while (shell->line[i] && !ft_in(shell->line[i], set))
			if (!ft_checks(shell->line, &i))
				exit (2); // ft_die() Error: unclosed quotes/parenthesis
		if (!i)
			while (shell->line[i] && ft_in(shell->line[i], set))
				i++;
		parsed = ft_extract_word(parsed, &dim, &i, &shell->line);
		if (!parsed)
			exit(1); // ft_die(); Error: memory error
	}
	return (parsed);
}
