/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:37:47 by gpanico           #+#    #+#             */
/*   Updated: 2023/03/28 07:56:14 by gpanico          ###   ########.fr       */
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

int	ft_parenthesis_check(char *line, int *i)
{
	int	par_count;

	if (line[*i] == ')')
		return (0); // ft_die(); Error: unclosed parenthesis
	else if (line[*i] == '(')
	{
		par_count = 1;
		(*i)++;
		while (line[*i] && par_count)
		{
			if (line[*i] == '(')
				par_count++;
			else if (line[*i] == ')')
				par_count--;
			if (!ft_quotes_check(line, i))
				return (0); // ft_die; Error: unclosed quotes
			(*i)++;
		}
		if (!line[*i] && par_count)
			return (0); // ft_die(); Error: unclosed parenthesis
		(*i)--;
	}
	return (1);
}

int	ft_checks(char *line, int *i)
{
	if (!ft_quotes_check(line, i))
		return (0); // ft_die() Error: unclosed quotes
	else if (!ft_parenthesis_check(line, i))
		return (0); // ft_die() Error: unclosed parenthesis
	(*i)++;
	return (1);
}
