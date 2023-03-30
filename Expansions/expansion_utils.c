/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:10:48 by adi-stef          #+#    #+#             */
/*   Updated: 2023/03/29 11:26:32 by adi-stef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	RETURN: this functions returns all the letters, numbers and underscores
//		right after the index [i] and before the first that's not a letter,
//		a number or an underscore
//	EXAMPLE: "Hello World!" if [i] it's 0 this function will return "ello"
char	*ft_getname(char *str, int i)
{
	int		j;
	char	*name;

	if (!str || i < 0 || i >= (int)ft_strlen(str))
		return (0);
	j = i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	if (str[j])
		j--;
	name = ft_substr(str, i + 1, j - i);
	return (name);
}

//	RETURN: from a string and an index i, this function returns the level of
//		subshell at the index i
int	ft_getlvl(char *str, int i)
{
	int	j;
	int	brackets;

	if (!str || i < 0 || i > (int)ft_strlen(str))
		return (0);
	j = -1;
	brackets = 0;
	while (++j < i)
	{
		if (!ft_getquotes(str, j) && str[j] == '(')
			brackets++;
		if (!ft_getquotes(str, j) && str[j] == ')')
			brackets--;
	}
	return (brackets);
}

//	RETURN: from a string [str] and an index [i] this function tells if i is
//		inside some quotes then tells the type of the quotes then returns 0
//	return types
//	[0] -> out of quotes
//	[1] -> inside single quotes
//	[2] -> inside double quotes
int	ft_getquotes(char *str, int i)
{
	int	quotes;
	int	j;

	if (!str || i < 0 || i > (int)ft_strlen(str))
		return (0);
	j = -1;
	quotes = 0;
	while (++j < i)
	{
		if (str[j] == '\'' && !quotes)
			quotes = 1;
		else if (str[j] == '\"' && !quotes)
			quotes = 2;
		else if (str[j] == '\'' && quotes == 1)
			quotes = 0;
		else if (str[j] == '\"' && quotes == 2)
			quotes = 0;
	}
	return (quotes);
}
