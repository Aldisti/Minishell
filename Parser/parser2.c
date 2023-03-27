/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:05:56 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/27 09:40:39 by gpanico          ###   ########.fr       */
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

int	ft_delete_spaces(t_shell *shell)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (shell->parsed[i])
	{
		trimmed = ft_strtrim(shell->parsed[i], " ");
		if (!trimmed)
			return (1);
		ft_free((void **) &shell->parsed[i]);
		shell->parsed[i] = trimmed;
		i++;
	}
	return (0);
}

int	ft_check_multi_par(char *line)
{
	int	i;
	int	par_count;
	int	count;
	int	index;

	i = 0;
	count = 0;
	par_count = 0;
	index = 0;
	while (line[i])
	{
		if (!par_count && index)
			count++;
		if (line[i] == '(')
		{
			index++;
			par_count++;
		}
		else if (line[i] == ')')
			par_count--;
		i++;
	}
	if (count != 1 && count)
		return (1);
	return (0);
}

void	ft_parser_checks(t_shell *shell)
{
	int	i;

	if (ft_delete_spaces(shell))
		exit(1); // ft_die; Error: memory error
	if (!shell->parsed)
		exit(1); // ft_die(); Error: memory error
	if (ft_in(shell->parsed[0][0], "&|"))
		exit(4); // ft_die(); Error: invalid command
	i = 0;
	while (shell->parsed[i])
	{
		if (ft_check_multi_par(shell->parsed[i]))
			exit(4); // ft_die(); Error: invalid command
		i++;
	}
}
