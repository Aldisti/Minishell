/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 17:10:48 by adi-stef          #+#    #+#             */
/*   Updated: 2023/04/17 12:40:21 by adi-stef         ###   ########.fr       */
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
	name = ft_substr(str, i, j - i + 1);
	return (name);
}

//	RETURN: from a string and an index i, this function returns the level of
//		subshell at the index i
int	ft_getlvl(char *str, int i)
{
	int	j;
	int	brackets;
	int	quotes;

	if (!str || i < 0 || i > (int)ft_strlen(str))
		return (0);
	j = -1;
	brackets = 0;
	while (++j < i)
	{
		quotes = ft_getquotes(str, j);
		if (!quotes && str[j] == '(')
			brackets++;
		if (!quotes && str[j] == ')')
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

/*
DESCRIPTION
it's like strstr (see man strstr)
this function searches the string [to_find] inside the strings array [tab]
and if found returns it's index inside the array [tab]
OUTPUT
[-1] -> if [to_find] is not found
*/
int	ft_find_in_array(char **tab, char *to_find)
{
	int	i;

	if (!tab || !to_find)
		return (-1);
	i = -1;
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], to_find))
			return (i);
	}
	return (-1);
}

/*
OUTPUT
[1] -> if there is something like: "echo ciao"
[0] -> if there is something like: "   echo" "echo   "
*/
int	ft_check_for_space(char *str)
{
	char	*trim;
	int		i;

	trim = ft_strtrim(str, " \t\n\v");
	if (!trim)
		return (0);
	i = -1;
	while (trim[++i])
	{
		if (ft_in(trim[i], " \t\n\v"))
		{
			ft_free((void **)&trim);
			return (1);
		}
	}
	ft_free((void **)&trim);
	return (0);
}
