/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpanico <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 08:47:18 by gpanico           #+#    #+#             */
/*   Updated: 2023/01/20 10:46:02 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft.h"

static size_t	ft_position(const char *s, char c, size_t counter);

static size_t	ft_count(const char *s, char c)
{
	size_t	n_word;
	size_t	i;

	i = 0;
	n_word = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] != 0)
		{
			n_word++;
			while (s[i] != c && s[i] != 0)
				i++;
		}
		if (s[i])
			i++;
	}
	return (n_word);
}

static size_t	ft_strlen2(const char *s, char c, size_t pos)
{
	size_t	i;

	i = 0;
	while (s[pos + i] && s[pos + i] != c)
		i++;
	return (i);
}

static char	*ft_cpword(const char *s, char c, size_t counter)
{
	size_t	start;
	size_t	len;
	size_t	i;
	char	*elem;

	start = ft_position(s, c, counter);
	len = ft_strlen2(s, c, start);
	elem = (char *) malloc ((len + 1) * sizeof (char));
	if (!elem)
		return (0);
	i = 0;
	while (i < len)
	{
		elem[i] = s[start + i];
		i++;
	}
	elem[i] = 0;
	return (elem);
}

static size_t	ft_position(const char *s, char c, size_t counter)
{
	size_t	pos;

	pos = 0;
	while (s[pos])
	{
		if (s[pos] != c)
		{
			if (counter)
				counter--;
			else
				return (pos);
			while (s[pos] != c)
				pos++;
		}
		if (s[pos])
			pos++;
	}
	return (pos);
}

char	**ft_split(const char *s, char c)
{
	char	**splitted;
	size_t	n_word;
	size_t	i;

	n_word = ft_count(s, c);
	splitted = (char **) malloc((n_word + 1) * sizeof (char *));
	if (!splitted)
		return (0);
	i = 0;
	while (i < n_word)
	{
		splitted[i] = ft_cpword(s, c, i);
		if (!splitted[i])
		{
			while (i--)
				free(splitted[i]);
			free(splitted);
			return (0);
		}
		i++;
	}
	splitted[i] = 0;
	return (splitted);
}
