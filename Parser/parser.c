/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:37:47 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/23 09:57:22 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_in(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	**ft_extract_word(char **parsed, int *dim, int *i, char **line)
{
	if (*i)
	{
		parsed = (char **)ft_realloc(parsed, sizeof(char *), *dim, *(dim) + 1);
		if (!parsed)
			return (NULL); // ft_die(); Error: memory error
		*(dim) = *(dim) + 1;
		parsed[*(dim) - 2] = ft_substr(*line, 0, *i);
		if (!parsed[*(dim) - 2])
			return (NULL); // ft_die(); Error: memory error
		*line = *line + *i;
		*i = 0;
		return (parsed);
	}
	else
		return (parsed);
}

int	ft_quotes_check(char *line, int	*i)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (!line[*i])
			return (0); // ft_die(); Error: unclosed quotes
	}
	else if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
		if (!line[*i])
			return (0); // ft_die(); Error: unclosed quotes
	}
	return (1);
}

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
		{
			if (!ft_quotes_check(shell->line, &i))
				exit (2); // ft_die() Error: unclosed quotes
			i++;
		}
		if (!i)
			while (shell->line[i] && ft_in(shell->line[i], set))
				i++;
		parsed = ft_extract_word(parsed, &dim, &i, &shell->line);
		if (!parsed)
			exit(1); // ft_die(); Error: memory error
	}
	return (parsed);
}
