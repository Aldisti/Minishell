/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaterno <mpaterno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:32:40 by mpaterno          #+#    #+#             */
/*   Updated: 2023/01/20 15:04:29 by mpaterno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_word_lenght(char const *str, int *j, char c)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[*j] && str[*j] == c)
		(*j)++;
	while (str[*j] && str[*j] != c)
	{
		i++;
		(*j)++;
	}
	temp = malloc((sizeof(char) * i) + 1);
	*j = *j - i;
	i = 0;
	while (str[*j] && str[*j] != c)
	{
		temp[i++] = str[*j];
		(*j)++;
	}
	temp[i] = 0;
	while (str[*j] && str[(*j)++] == c)
	{
	}
	(*j)--;
	return (temp);
}

int	word_counter(char const *str, char c)
{
	int	i;
	int	flag;
	int	counter;

	counter = 0;
	i = -1;
	flag = 1;
	while (str[++i])
	{
		if (str[i] != c && flag)
		{
			flag = 0;
			counter++;
		}
		else if (str[i] == c)
			flag = 1;
	}
	return (counter);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	int		words;
	char	**strs;

	if (!str)
		return (0);
	j = 0;
	words = word_counter(str, c);
	strs = malloc((words + 1) * sizeof(char *));
	if (!strs)
		return (0);
	i = -1;
	while (++i < words)
		strs[i] = get_word_lenght(str, &j, c);
	strs[words] = 0;
	return (strs);
}
