/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:36:09 by mpaterno          #+#    #+#             */
/*   Updated: 2023/04/04 22:17:21 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

char	**ft_extract_word_command(char **parsed, int *dim, int *i, char **line)
{
	if (*i)
	{
		parsed = (char **)ft_realloc(parsed, sizeof(char *), *dim, *(dim) + 1);
		if (!parsed)
			return (NULL);
		*(dim) = *(dim) + 1;
		parsed[*(dim) - 2] = ft_substr(*line, 0, *i);
		if (!parsed[*(dim) - 2])
			return (NULL);
		*line = *line + *i;
		*i = 0;
		return (parsed);
	}
	else
		return (parsed);
}

int	ft_quotes_check_command(char *line, int	*i)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (!line[*i])
			return (0);
	}
	else if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
		if (!line[*i])
			return (0);
	}
	return (1);
}

char	**command_parser(char *str, char *set)
{
	int		dim;
	int		i;
	char	**parsed;

	parsed = (char **)ft_calloc(sizeof(char *), 1);
	if (!parsed)
		exit(1);
	dim = 1;
	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_in(str[i], set))
		{
			if (!ft_quotes_check_command(str, &i))
				exit (2);
			i++;
		}
		if (!i)
			while (str[i] && ft_in(str[i], set))
				i++;
		parsed = ft_extract_word_command(parsed, &dim, &i, &str);
		if (!parsed)
			exit(1);
	}
	return (parsed);
}
