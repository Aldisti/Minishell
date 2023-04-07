/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-stef <adi-stef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:37:47 by gpanico           #+#    #+#             */
/*   Updated: 2023/04/07 09:41:02 by gpanico          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * Description:	checks if the character 'c' is in the given set of character.
 * Input:	the character c and the set given as a C string
 * 		(i.e. null terminated string).
 * Output:	returns an integer:
 * 			-0 if 'c' isn't in the given set.
 * 			-1 if 'c' is int the given set.
*/
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

/*
 * Description:	allocates a new string in the array 'parsed' and stores
 * 		the substring which starts at the beginning and ends at 
 * 		the index '*i' of '*line'; both the index and the string 
 * 		are given by reference cause at the end both values are 
 * 		changed:
 * 			-the index is set to zero;
 * 			-the pointer to the first character of the string
 * 			is moved after the substring.
 * Input:	the array of string ('parsed') and its dimension
 * 		(i.e. the number of strings in the array 
 * 		included the NULL pointer at the end),
 * 		the latest is passed by reference since it will be
 * 		updated to the new dimension of the array;
 * 		the last two arguments are the index and the string,
 * 		both passed by reference (see above).
 * Output:	the new strings array.
*/
char	**ft_extract_word(char **parsed, int *dim, int *i, char **line)
{
	char	**tmp;

	if (*i)
	{
		tmp = (char **)ft_realloc(parsed, sizeof(char *),
				*dim, *(dim) + 1);
		if (!tmp)
		{
			ft_free_mat((void ***) &parsed);
			return (NULL);
		}
		parsed = tmp;
		*(dim) = *(dim) + 1;
		parsed[*(dim) - 2] = ft_substr(*line, 0, *i);
		if (!parsed[*(dim) - 2])
		{
			ft_free_mat((void ***) &parsed);
			return (NULL);
		}
		*line = *line + *i;
		*i = 0;
	}
		return (parsed);
}

/*
 * Description:	if the given string has a single/double quotes at index '*i'
 * 		moves it until another matching quotes is found;
 * 		if the matching quotes aren't found the function raises 
 * 		an error (i.d. returns 0).
 * Input:	the string to check and the index ('*i') representing
 * 		the starting point of the string.
 * Output:	returns an integer:
 * 			-0 if the founded quotes aren't closed;
 * 			-1 if the quotes are closed or if
 * 			there aren't found;
*/
int	ft_quotes_check(char *line, int	*i)
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

/*
 * Description:	checks if the given string has parentheses at
 * 		index '*i', if an open one is found moves
 * 		the '*i' until the closed parentheses; if
 * 		a close parenthesis is found at the beginning or
 * 		isn't found after an open parentheses the function
 * 		raises an error.
 * Input:	the string to check and the index ('*i') representing
 * 		the starting point of the string.
 * Output:	returns an integer:
 * 			-0 if the founded parentheses aren't closed;
 * 			-1 if the parentheses are closed or if
 * 			there aren't;
*/
int	ft_parenthesis_check(char *line, int *i)
{
	int	par_count;

	if (line[*i] == ')')
		return (0);
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
				return (0);
			(*i)++;
		}
		if (!line[*i] && par_count)
			return (0);
		(*i)--;
	}
	return (1);
}

/*
 * Description:	checks if the given string has unclosed parentheses
 * 		or quotes, if parentheses or quotes are found at index
 * 		'*i' it is moved to the closed ones; if not moves the
 * 		index to the next character.
 * Input:	the string to check and the index ('*i') representing
 * 		the starting point of the string.
 * Output:	returns an integer:
 * 			-0 if the founded parentheses/quotes aren't closed;
 * 			-1 if the parentheses/quotes are closed or if
 * 			there aren't found;
*/
int	ft_checks(char *line, int *i)
{
	if (!ft_quotes_check(line, i))
	{
		printf("Bad Syntax: unclosed quotes.\n");
		return (0);
	}
	else if (!ft_parenthesis_check(line, i))
	{
		printf("Bad Syntax: unclosed parentheses.\n");
		return (0);
	}
	(*i)++;
	return (1);
}
