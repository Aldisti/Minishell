/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:36:09 by mpaterno          #+#    #+#             */
/*   Updated: 2023/03/22 15:58:20 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

void	*mft_realloc(void *p, size_t size, int dim, int new_dim)
{
	char		*new_p;
	size_t		i;

	new_p = (char *)malloc(size * new_dim);
	if (!new_p)
		return (NULL);
	i = 0;
	while (i < size * new_dim)
	{
		if (i < size * dim)
			new_p[i] = ((char *) p)[i];
		else
			new_p[i] = 0;
		i++;
	}
	free(p);
	return ((void *) new_p);
}

int	ft_in_command(char c, char *set)
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

char	**ft_extract_word_command(char **parsed, int *dim, int *i, char **line)
{
	if (*i)
	{
		parsed = (char **)mft_realloc(parsed, sizeof(char *), *dim, *(dim) + 1);
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

int	ft_quotes_check_command(char *line, int	*i)
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

char	**command_parser(char *str, char *set)
{
	int		dim;
	int		i;
	char	**parsed;

	parsed = (char **)ft_calloc(sizeof(char *), 1);
	if (!parsed)
		exit(1); // ft_die(); Error: memory error
	dim = 1;
	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_in_command(str[i], set))
		{
			if (!ft_quotes_check_command(str, &i))
				exit (2); // ft_die() Error: unclosed quotes
			i++;
		}
		if (!i)
			while (str[i] && ft_in_command(str[i], set))
				i++;
		parsed = ft_extract_word_command(parsed, &dim, &i, &str);
		if (!parsed)
			exit(1); // ft_die(); Error: memory error
	}
	return (parsed);
}
